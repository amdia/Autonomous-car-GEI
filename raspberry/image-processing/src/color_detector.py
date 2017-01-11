import cv2
import numpy as np


class ColorFilter:
    """
    This class provides a simple method for color filtering based on the HSV color space, the image sample needs to be
    blurred before being passed to this filter
    """

    DEFAULT_COLOR_THRESHOLDS = [np.array([0, 0, 20]), np.array([200, 40, 200])]   # kinda gray, for road detection

    def __init__(self):
        """
        Class constructor, set all attributes to their default values
        :return: None
        """
        self.__img = None
        self.__mask = None
        self.__colorThresholds = ColorFilter.DEFAULT_COLOR_THRESHOLDS

    @property
    def color_thresholds(self):
        """
        Get the lower and upper threshold for color filtering
        :return: an array contained two numpy arrays of thresholds
        """
        return self.__colorThresholds

    @color_thresholds.setter
    def color_thresholds(self, lower, upper):
        """
        Set the lower and upper threshold for color filtering
        :param lower: numpy array of lower threshold, e.g numpy.array([v1, v2, v3])
        :param upper: numpy array of upper threshold, e.g numpy.array([v1, v2, v3])
        :return: None
        """
        self.__colorThresholds[0] = lower
        self.__colorThresholds[1] = upper

    @property
    def img(self):
        """
        Get the image before filtered
        :return: img
        """
        return self.__img

    @img.setter
    def img(self, image):
        """
        Set the image for filtering
        :param image: the image for filtering
        :return: None
        """
        self.__img = image

    @property
    def mask(self):
        """
        Get the mask after processing
        :return: the mask
        """
        return self.__mask

    def process(self):
        """
        Start processing
        :return: None
        """
        try:
            hsv = cv2.cvtColor(self.__img, cv2.COLOR_BGR2HSV)
            self.__mask = cv2.inRange(hsv, self.__colorThresholds[0], self.__colorThresholds[1])
        except cv2.error:
            print("process: image not found!!!")

    def display(self, raw_img=True):
        """
        Display the mask and the raw image
        :param raw_img: if True, the raw image will be displayed
        :return: None
        """
        cv2.imshow('mask', self.__mask)
        if raw_img:
            cv2.imshow('raw image', self.__img)


if __name__ == '__main__':
    roadDetect = ColorFilter()
    img = cv2.imread('../img/road.jpg')
    img = cv2.resize(img, (640, 480))
    img = cv2.blur(img, (10, 10))
    roadDetect.img = img
    roadDetect.process()
    roadDetect.display()
    cv2.waitKey(0)
