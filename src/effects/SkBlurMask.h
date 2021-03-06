
/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef SkBlurMask_DEFINED
#define SkBlurMask_DEFINED

#include "SkShader.h"
#include "SkMask.h"

class SkBlurMask {
public:
    enum Style {
        kNormal_Style,  //!< fuzzy inside and outside
        kSolid_Style,   //!< solid inside, fuzzy outside
        kOuter_Style,   //!< nothing inside, fuzzy outside
        kInner_Style,   //!< fuzzy inside, nothing outside

        kStyleCount
    };

    enum Quality {
        kLow_Quality,   //!< box blur
        kHigh_Quality   //!< three pass box blur (similar to gaussian)
    };

    static bool BlurRect(SkMask *dst, const SkRect &src,
                         SkScalar radius, Style style,
                         SkIPoint *margin = NULL,
                         SkMask::CreateMode createMode=SkMask::kComputeBoundsAndRenderImage_CreateMode);
    static bool Blur(SkMask* dst, const SkMask& src,
                     SkScalar radius, Style style, Quality quality,
                     SkIPoint* margin = NULL);

    // the "ground truth" blur does a gaussian convolution; it's slow
    // but useful for comparison purposes.

    static bool BlurGroundTruth(SkMask* dst, const SkMask& src,
                           SkScalar provided_radius, Style style,
                           SkIPoint* margin = NULL);

    // scale factor for the blur radius to match the behavior of the all existing blur
    // code (both on the CPU and the GPU).  This magic constant is  1/sqrt(3).
    // TODO: get rid of this fudge factor and move any required fudging up into
    // the calling library
    static const SkScalar kBlurRadiusFudgeFactor;

};

#endif
