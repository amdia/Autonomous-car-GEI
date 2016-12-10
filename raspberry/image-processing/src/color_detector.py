import cv2
import numpy as np


class ColorFilter:
    """
    This class provides a simple method for color filtering based on the HSV color space
    """

    DEFAULT_BLUR_FACTOR = (10, 10)
    DEFAULT_IMG_RESOLUTION = (640, 480)
    DEFAULT_CROP_SIZE = [0, 500, 150, 350]
    DEFAULT_COLOR_THRESHOLDS = [np.array([80, 5, 20]), np.array([200, 120, 200])]   # kinda gray, for road detection

    def __init__(self):
        """
        Class constructor, set all attributes to their default values
        :return: None
        """
        self._rawImg = None
        self._mask = None
        self._size = ColorFilter.DEFAULT_IMG_RESOLUTION
        self._cropSize = ColorFilter.DEFAULT_CROP_SIZE
        self._blurFactor = ColorFilter.DEFAULT_BLUR_FACTOR
        self._colorThresholds = ColorFilter.DEFAULT_COLOR_THRESHOLDS

    def set_thresholds(self, lower, upper):
        """
        Set the lower and upper threshold for color filtering
        :param lower: numpy array of lower threshold, e.g numpy.array([v1, v2, v3])
        :param upper: numpy array of upper threshold, e.g numpy.array([v1, v2, v3])
        :return: None
        """
        self._colorThresholds[0] = lower
        self._colorThresholds[1] = upper

    def set_blur_factor(self, factor):
        """
        Set the blur factor for smoothing image
        :param factor: a 1x2 tuple, e.g (10, 10)
        :return: None
        """
        self._blurFactor = factor

    def set_crop_size(self, x1, x2, y1, y2):
        """
        Set the image ROI, we only process this part of image
        :param x1: start point of x axis
        :param x2: stop point of x axis
        :param y1: start point of y axis
        :param y2: stop point of y axis
        :return: None
        """
        self._cropSize[0] = x1
        self._cropSize[1] = x2
        self._cropSize[2] = y1
        self._cropSize[3] = y2

    def get_raw_img(self):
        """
        Get the raw image before processing
        :return: the full size raw image
        """
        return self._rawImg

    def get_mask(self):
        """
        Get the mask after processing
        :return: the mask
        """
        return self._mask

    def process(self, image):
        """
        Start processing, resize -> crop -> denoise -> filter
        :param image: the image to be processed
        :return: None
        """
        self._rawImg = image
        if self._size is not None:
            self._rawImg = cv2.resize(self._rawImg, self._size)
        cropped = self._rawImg[self._cropSize[2]:self._cropSize[3], self._cropSize[0]:self._cropSize[1]]
        denoise = cv2.blur(cropped, self._blurFactor)
        hsv = cv2.cvtColor(denoise, cv2.COLOR_BGR2HSV)
        self._mask = cv2.inRange(hsv, self._colorThresholds[0], self._colorThresholds[1])

    def display(self, raw_img=True):
        """
        Display the mask and the raw image
        :param raw_img: if True, the raw image will be displayed
        :return:
        """
        cv2.imshow('mask', self._mask)
        if raw_img:
            cv2.imshow('raw image', self._rawImg)


if __name__ == '__main__':
    roadDetect = ColorFilter()
    img = cv2.imread('../img/road.jpg')
    roadDetect.process(img)
    roadDetect.display()
    cv2.waitKey(0)
