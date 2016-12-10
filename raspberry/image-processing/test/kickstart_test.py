import numpy as np
import cv2

# Recommended constants
DENOISE_TEMPLATE_WIN_SIZE = 7
DENOISE_SEARCH_WIN_SIZE = 21
HOUGH_LINE_RHO_RESOLUTION = 1
HOUGH_LINE_THETA_RESOLUTION = np.pi / 180.0

# Parameters
IMG_SIZE = (500, 450)
DENOISE_POWER = 30
HOUGH_LINE_THRESHOLD = 10

if __name__ == '__main__':

    def onMouse(event, x, y, flag, param):
        if event == cv2.EVENT_LBUTTONDOWN:
            print(param[y][x])

    img = cv2.imread("../img/road_6.jpg")
    img = cv2.resize(img, IMG_SIZE)

    denoise = cv2.fastNlMeansDenoising(img, None, DENOISE_POWER, DENOISE_TEMPLATE_WIN_SIZE, DENOISE_SEARCH_WIN_SIZE)
    color_converted = cv2.cvtColor(denoise, cv2.COLOR_BGR2HSV)
    mask_grass = cv2.inRange(color_converted, (10, 50, 20), (75, 180, 200))
    mask_road = cv2.inRange(color_converted, (80, 5, 20), (200, 120, 200))
    edges = cv2.Canny(mask_road, 20, 150)
    lines = cv2.HoughLinesP(edges, HOUGH_LINE_RHO_RESOLUTION,
                            HOUGH_LINE_THETA_RESOLUTION, HOUGH_LINE_THRESHOLD,
                            None, 5)

    for l in range(len(lines)):
        cv2.line(denoise, (lines[l][0][0], lines[l][0][1]), (lines[l][0][2], lines[l][0][3]), (0, 0, 255), thickness=2)

    cv2.imshow("edges", edges)
    cv2.imshow("converted", color_converted)
    cv2.imshow("denoised", denoise)
    cv2.imshow("mask", mask_road)
    cv2.setMouseCallback("converted", onMouse, param=color_converted)

    cv2.waitKey()
