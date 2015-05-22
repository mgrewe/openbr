#include <openbr/plugins/openbr_internal.h>

using namespace cv;

namespace br
{

class NPDRepresentation : public Representation
{
    Q_OBJECT

    Q_PROPERTY(int winWidth READ get_winWidth WRITE set_winWidth RESET reset_winWidth STORED false)
    Q_PROPERTY(int winHeight READ get_winHeight WRITE set_winHeight RESET reset_winHeight STORED false)
    BR_PROPERTY(int, winWidth, 24)
    BR_PROPERTY(int, winHeight, 24)

    void init()
    {
        for (int p1 = 0; p1 < (winWidth * winHeight); p1++)
            for (int p2 = p1; p2 < (winWidth * winHeight); p2++)
                features.append(Feature(p1, p2));
    }

    float evaluate(const Mat &image, int idx) const
    {
        return features[idx].calc(image);
    }

    Size windowSize(int *dx, int *dy) const
    {
        if (dx && dy)
            *dx = *dy = 0;
        return Size(winWidth, winHeight);
    }

    struct Feature
    {
        Feature() {}
        Feature(int p1, int p2) { p[0] = p1; p[1] = p2; }
        float calc(const Mat &image) const;

        int p[2];
    };
    QList<Feature> features;
};

BR_REGISTER(Representation, NPDRepresentation)

} // namespace br

#include "representation/npd.moc"
