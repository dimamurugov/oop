#ifndef GEOMETRICFIGURES_CPOINT_H
#define GEOMETRICFIGURES_CPOINT_H

class CPoint {
public:
    CPoint(double x, double y);
    std::vector<double> GetPoints();
private:
    double m_x;
    double m_y;
};

#endif //GEOMETRICFIGURES_CPOINT_H
