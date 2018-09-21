import numpy as np  # Module that simplifies computations on matrices
# import matplotlib.pyplot as plt  # Module used for plotting
from pylsl import StreamInlet, resolve_byprop  # Module to receive EEG data
import utils  # Our own utility functionsi
import os
from math import floor


def readingsFunc(numloops=None):
    if numloops:  # use this for tests
        count = 0

    # define the indices for the brain waves
    bandAlpha = 2
    bandDelta = 0
    bandTheta = 1
    bandBeta = 3

    # Length of the EEG data buffer (in seconds)
    # This buffer will hold last n seconds of data and be used for calculations
    BUFFER_LENGTH = 1

    # Length of the epochs used to compute the FFT (in seconds)
    EPOCH_LENGTH = 1

    # Amount of overlap between two consecutive epochs (in seconds)
    OVERLAP_LENGTH = 0.8

    # Amount to 'shift' the start of each next consecutive epoch
    SHIFT_LENGTH = EPOCH_LENGTH - OVERLAP_LENGTH

    # Index of the channel(s) (electrodes) to be used
    # 0 = left ear, 1 = left forehead, 2 = right forehead, 3 = right ear
    INDEX_CHANNEL = [0]
    """ 1. CONNECT TO EEG STREAM """

    # Search for active LSL streams
    print('Looking for an EEG stream...')
    streams = resolve_byprop('type', 'EEG', timeout=20)
    if len(streams) == 0:
        raise RuntimeError('Can\'t find EEG stream.')

    # Set active EEG stream to inlet and apply time correction
    print("Start acquiring data")
    inlet = StreamInlet(streams[0], max_chunklen=12)
    eeg_time_correction = inlet.time_correction()

    # Get the stream info and description
    info = inlet.info()
    description = info.desc()

    # Get the sampling frequency
    # This is an important value that represents how many EEG data points are
    # collected in a second. This influences our frequency band calculation.
    # for the Muse 2016, this should always be 256
    fs = int(info.nominal_srate())

    """ 2. INITIALIZE BUFFERS """

    # Initialize raw EEG data buffer
    eeg_buffer = np.zeros((int(fs * BUFFER_LENGTH), 1))
    filter_state = None  # for use with the notch filter

    # Compute the number of epochs in "buffer_length"
    n_win_test = int(np.floor((BUFFER_LENGTH - EPOCH_LENGTH) /
                              SHIFT_LENGTH + 1))

    # Initialize the band power buffer (for plotting)
    # bands will be ordered: [delta, theta, alpha, beta]
    band_buffer = np.zeros((n_win_test, 4))

    try:
        # The following loop acquires data, computes band powers, and calculates neurofeedback metrics based on those band powers
        maxMetric = 0
        minMetric = 100
        loopCount = 0
        minMetricCount = 0

        while True:

            """ 3.1 ACQUIRE DATA """
            # Obtain EEG data from the LSL stream
            eeg_data, timestamp = inlet.pull_chunk(
                timeout=1, max_samples=int(SHIFT_LENGTH * fs))

            # Only keep the channel we're interested in
            ch_data = np.array(eeg_data)[:, INDEX_CHANNEL]

            # Update EEG buffer with the new data
            eeg_buffer, filter_state = utils.update_buffer(
                eeg_buffer, ch_data, notch=True,
                filter_state=filter_state)

            """ 3.2 COMPUTE BAND POWERS """
            # Get newest samples from the buffer
            data_epoch = utils.get_last_data(eeg_buffer,
                                             EPOCH_LENGTH * fs)

            # Compute band powers
            band_powers = utils.compute_band_powers(data_epoch, fs)
            band_buffer, _ = utils.update_buffer(band_buffer,
                                                 np.asarray([band_powers]))
            # Compute the average band powers for all epochs in buffer
            # This helps to smooth out noise
            smooth_band_powers = np.mean(band_buffer, axis=0)

            # print('Delta: ', band_powers[bandDelta], ' Theta: ', band_powers[bandTheta],
            #       ' Alpha: ', band_powers[bandAlpha], ' Beta: ', band_powers[bandBeta])

            # Added this to the function
            ind = np.unravel_index(np.argmax(band_powers, axis=None), band_powers.shape)

            if ind == bandTheta:
                print("Theta")

            elif ind == bandAlpha:
                print("Alpha")

            else:
                print("Beta")

            #
            # stringToSend = "python3 ~/MyProjects/Beakerhead/rpi-rf/scripts/rpi-rf_send {0}".format(
            #     int(ThetaState))
            #
            # os.system(stringToSend)
            #
            # print("playing the stupid fucking value that we hate which is: {0}".format(
            #     int(ThetaState)))

            """ 3.3 COMPUTE NEUROFEEDBACK METRICS """
            # These metrics could also be used to drive brain-computer interfaces

            # Alpha Protocol:
            # Simple redout of alpha power, divided by delta waves in order to rule out noise
            # alpha_metric = smooth_band_powers[bandAlpha] / \
            #     smooth_band_powers[bandDelta]
            # print("Alpha Concentration: ", alpha_metric)

            # if alpha_metric > maxMetric:
            #     maxMetric = alpha_metric
            #
            # if alpha_metric < minMetric:
            #     minMetric = alpha_metric
            #     if minMetric < 0:
            #         minMetricCount = minMetricCount + 1
            # loopCount = loopCount + 1
            # print('Alpha Relaxation: {0},  Maximum: {1},   Minimum: {2}, Under Zero: {3}, totalLoop: {4}'.format(
            #     alpha_metric, maxMetric, minMetric, minMetricCount, loopCount))

            # Beta Protocol:
            # Beta waves have been used as a measure of mental activity and concentration
            # This beta over theta ratio is commonly used as neurofeedback for ADHD
            # beta_metric = smooth_band_powers[bandBeta] / \
            #     smooth_band_powers[bandTheta]
            # print('Beta Concentration: ', beta_metric)

            # Alpha/Theta Protocol:
            # This is another popular neurofeedback metric for stress reduction
            # Higher theta over alpha is supposedly associated with reduced anxiety
            theta_metric = smooth_band_powers[bandTheta] / \
                smooth_band_powers[bandAlpha]

            #chkMetrics = np.array([alpha_metric, beta_metric, theta_metric])

            # print(chkMetrics)
            # Added this to the function
            #ind_metric = np.unravel_index(np.argmax(chkMetrics, axis=None), chkMetrics.shape)

            # if ind_metric == 0:
            #     print("Alpha Metric")
            #
            # elif ind == 1:
            #     print("Beta Metric")
            #
            # else:
            #     print("Theta Metric")
            print "Theta Metris is : ", theta_metric
            ThetaState = floor(theta_metric*2)
            if ThetaState > 3:
                ThetaState = 3
            elif ThetaState < 1:
                ThetaState = 1

            stringToSend = "python3 ~/MyProjects/Beakerhead/rpi-rf/scripts/rpi-rf_send {0}".format(
                int(ThetaState))
            print(stringToSend)
            os.system(stringToSend)
            # print('Theta Relaxation: ', theta_metric)

            if numloops:
                count += 1
                if count > numloops:
                    break

    except KeyboardInterrupt:
        print('Closing!')


if __name__ == "__name__":
    readingsFunc()
