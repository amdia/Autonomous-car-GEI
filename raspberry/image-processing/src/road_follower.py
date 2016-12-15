import src.color_detector as cd
import cv2


class RoadFollower:

    # frame's factors
    __IMG_SIZE = (640, 480)
    __BLUR_K_SIZE = (10, 10)
    # horizontal window crop
    __HW_X1 = 0
    __HW_Y1 = 150
    __HW_X2 = __IMG_SIZE[0]
    __HW_Y2 = __HW_Y1 + 200
    # vertical window crop
    __VW_X1 = 250
    __VW_Y1 = 100
    __VW_X2 = __VW_X1 + 140
    __VW_Y2 = __VW_Y1 + 250

    def __init__(self):
        self.__colorDetectV = cd.ColorFilter()
        self.__colorDetectH = cd.ColorFilter()

    def update_frame(self, image):
        if image.shape[0] != RoadFollower.__IMG_SIZE[1] or image.shape[1] != RoadFollower.__IMG_SIZE[0]:
            image = cv2.resize(image, RoadFollower.__IMG_SIZE)
        image = cv2.blur(image, RoadFollower.__BLUR_K_SIZE)
        self.__colorDetectH.img = image[RoadFollower.__HW_Y1:RoadFollower.__HW_Y2,
                                        RoadFollower.__HW_X1:RoadFollower.__HW_X2]
        self.__colorDetectV.img = image[RoadFollower.__VW_Y1:RoadFollower.__VW_Y2,
                                        RoadFollower.__VW_X1:RoadFollower.__VW_X2]

    def set_thresholds(self, v_thresh, h_thresh):
        self.__colorDetectV.color_thresholds = v_thresh
        self.__colorDetectH.color_thresholds = h_thresh

    def filter(self):
        self.__colorDetectV.process()
        self.__colorDetectH.process()

    def display_masks(self):
        cv2.imshow('mask V', self.__colorDetectV.mask)
        cv2.imshow('mask H', self.__colorDetectH.mask)


if __name__ == '__main__':
    img = cv2.imread('../img/road.jpg')
    road_follow = RoadFollower()
    road_follow.update_frame(img)
    road_follow.filter()
    road_follow.display_masks()
    cv2.waitKey(0)
