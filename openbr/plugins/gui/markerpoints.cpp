/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright 2012 The MITRE Corporation                                      *
 *                                                                           *
 * Licensed under the Apache License, Version 2.0 (the "License");           *
 * you may not use this file except in compliance with the License.          *
 * You may obtain a copy of the License at                                   *
 *                                                                           *
 *     http://www.apache.org/licenses/LICENSE-2.0                            *
 *                                                                           *
 * Unless required by applicable law or agreed to in writing, software       *
 * distributed under the License is distributed on an "AS IS" BASIS,         *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 * See the License for the specific language governing permissions and       *
 * limitations under the License.                                            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <openbr/plugins/openbr_internal.h>
#include <openbr/core/opencvutils.h>
#include <cmath>

using namespace cv;

namespace br
{

/*!
 * \ingroup transforms
 * \brief Renders metadata onto the image.
 *
 * The inPlace argument controls whether or not the image is cloned before the metadata is drawn.
 *
 * \author Josh Klontz \cite jklontz
 */
class MarkerPointsTransform : public UntrainableTransform
{
    Q_OBJECT
    Q_PROPERTY(bool verbose READ get_verbose WRITE set_verbose RESET reset_verbose STORED false)
    /*
    Q_PROPERTY(bool points READ get_points WRITE set_points RESET reset_points STORED false)
    Q_PROPERTY(bool rects READ get_rects WRITE set_rects RESET reset_rects STORED false)
    Q_PROPERTY(bool inPlace READ get_inPlace WRITE set_inPlace RESET reset_inPlace STORED false)
    */
    Q_PROPERTY(int lineThickness READ get_lineThickness WRITE set_lineThickness RESET reset_lineThickness STORED false)
    /*
    Q_PROPERTY(bool named READ get_named WRITE set_named RESET reset_named STORED false)
    Q_PROPERTY(bool location READ get_location WRITE set_location RESET reset_location STORED false)
    */
    BR_PROPERTY(bool, verbose, false)
    /*
    BR_PROPERTY(bool, points, true)
    BR_PROPERTY(bool, rects, true)
    BR_PROPERTY(bool, inPlace, false)
    */
    BR_PROPERTY(int, lineThickness, 1)
    /*
    BR_PROPERTY(bool, named, true)
    BR_PROPERTY(bool, location, true)
    */

    void project(const Template &src, Template &dst) const
    {
    	dst=src;

    	const Scalar color(0,0,255);
        const Scalar verboseColor(255, 255, 0);
        cv::Size size (640,480);

		const QList<Point2f> pointsList = OpenCVUtils::toPoints(src.m());
		Point2f minima = OpenCVUtils::getMinimumElements(pointsList);
		Point2f maxima = OpenCVUtils::getMaximumElements(pointsList);

		Point2f::value_type rangeX = std::abs(minima.x - maxima.x);
		Point2f::value_type rangeY = std::abs(minima.y - maxima.y);

		dst.m() = cv::Mat(size,CV_8UC3,cv::Scalar(255,255,255));

		for (int i=0; i<pointsList.size(); i++) {
			Point2f point = pointsList[i];
			point -= minima;
			point.x /= (rangeX / size.width);
			point.y /= (rangeY / size.height);
			circle(dst, point, 3, color, -1);
			//QString label = (location) ? QString("%1,(%2,%3)").arg(QString::number(i),QString::number(point.x),QString::number(point.y)) : QString("%1").arg(QString::number(i));
			//if (verbose) putText(dst, label.toStdString(), point, FONT_HERSHEY_SIMPLEX, 0.5, verboseColor, 1);
		}
//        if (rects) {
//            foreach (const Rect &rect, OpenCVUtils::toRects(src.file.namedRects() + src.file.rects()))
//                rectangle(dst, rect, color, lineThickness);
//        }
    }
};

BR_REGISTER(Transform, MarkerPointsTransform)

} // namespace br

#include "gui/markerpoints.moc"
