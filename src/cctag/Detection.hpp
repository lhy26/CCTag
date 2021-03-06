/*
 * Copyright 2016, Simula Research Laboratory
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef VISION_CCTAG_DETECTION_HPP_
#define VISION_CCTAG_DETECTION_HPP_

#include <cctag/CCTag.hpp>
#include <cctag/CCTagMarkersBank.hpp>
#include <cctag/Types.hpp>
#include <cctag/Params.hpp>
#include <cctag/utils/LogTime.hpp>

#include <opencv2/opencv.hpp>

#include <cstddef>
#include <string>
#include <vector>

namespace cctag {

class EdgePoint;
class EdgePointImage;

/**
 * @brief Perform the CCTag detection on a gray scale image. Cf. application/detection/main.cpp for example of usage.
 * 
 * @param[out] markers Detected markers. WARNING: only markers with status == 1 are valid ones. (status available via getStatus()) 
 * @param[in] pipeId Choose one of up to 3 parallel CUDA pipes
 * @param[in] frame A frame number. Can be anything (e.g. 0).
 * @param[in] imgGraySrc Gray scale input image.
 * @param[in] providedParams Contains all the parameters.
 * @param[in] bank CCTag bank.
 * @param[in] bDisplayEllipses No longer used.
 */
void cctagDetection(
        CCTag::List& markers,
        int          pipeId,
        const std::size_t frame,
        const cv::Mat & graySrc,
        const Parameters & params,
        const cctag::CCTagMarkersBank & bank,
        const bool bDisplayEllipses = true,
        logtime::Mgmt* durations = 0 );

void cctagDetectionFromEdges(
        CCTag::List&            markers,
        EdgePointCollection& edgeCollection,
        const cv::Mat&          src,
        const std::vector<EdgePoint*>& seeds,
        const std::size_t       frame,
        int pyramidLevel,
        float scale,
        const Parameters & params,
        logtime::Mgmt* durations );

void createImageForVoteResultDebug(
        const cv::Mat & src,
        std::size_t nLevel);

} // namespace cctag

#endif

