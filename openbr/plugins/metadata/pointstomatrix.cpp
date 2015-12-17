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
#include <iostream>

namespace br
{

/*!
 * \ingroup transforms
 * \brief Converts either the file::points() list or a QList<QPointF> metadata item to be the template's matrix
 * \author Scott Klum \cite sklum
 */
class PointsToMatrixTransform : public UntrainableTransform
{
    Q_OBJECT

    Q_PROPERTY(QString inputVariable READ get_inputVariable WRITE set_inputVariable RESET reset_inputVariable STORED false)
    Q_PROPERTY(int pos READ get_pos WRITE set_pos RESET reset_pos STORED false)
	Q_PROPERTY(int length READ get_length WRITE set_length RESET reset_length STORED false)
    BR_PROPERTY(QString, inputVariable, QString())
    BR_PROPERTY(int , pos, 0)
	BR_PROPERTY(int , length, -1)

    void project(const Template &src, Template &dst) const
    {
    	QList<QPointF> res;

        dst = src;

        if (inputVariable.isEmpty()) {
			res = dst.file.points();
        } else {
            if (src.file.contains(inputVariable))
                res = dst.file.get<QList<QPointF> >(inputVariable);
        }

        if (length > 0 && length+pos > res.length())
        	qFatal("wrong pos or length given.");
        else
        	res = res.mid(pos,length);

        dst.m() = OpenCVUtils::pointsToMatrix(res);


    }
};

BR_REGISTER(Transform, PointsToMatrixTransform)

} // namespace br

#include "metadata/pointstomatrix.moc"
