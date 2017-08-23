#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <cfloat>

using namespace std;
#define epsilon 2.2204460492503131e-016  /* smallest float value such that 1->0+DBL_EPSILON != 1->0 */

struct point
{
    float x;
    float y;
};
point lineIntersection(point p1, point q1, point p2, point q2)
{
    float a1 = q1.y - p1.y;
    float b1 = p1.x - q1.x;
    float c1 = a1*(p1.x) + b1*(p1.y);

    float a2 = q2.y - p2.y;
    float b2 = p2.x - q2.x;
    float c2 = a2*(p2.x) + b2*(p2.y);
    float det = a1*b2 - a2*b1;
    if (det == 0)
    {
        //cout << "Do not intersect\n";
        point pt = {FLT_MAX, FLT_MAX};
        return pt; 
    }
    else
    {
        float x = (b2*c1 - b1*c2)/det;
        float y = (a1*c2 - a2*c1)/det;
        if(x >= min(p1.x, q1.x) && x<= max(p1.x,q1.x) && 
            y >= min(p1.y, q1.y) && y<= max(p1.y, q1.y) &&
            x >= min(p2.x, q2.x) && x<= max(p2.x,q2.x) &&
            y >= min(p2.y, q2.y) && y<= max(p2.y,q2.y))
        {
            point pt = {x,y};
            return pt;
        }
        else
        {
            //cout << "Line segments do not intersect";
            point pt = {FLT_MAX, FLT_MAX};

            return pt;
        }
    }
}
/*bool isBetween(point * a, point * b, point *c)
{
    float crossproduct = (c->y - a->y)*(b->x - a->x) - (c->x - a->x)*(b->y - a->y);
    if (abs(crossproduct) > epsilon)
    {
        return false;
    }
    float dotproduct = (c->x - a->x)*(b->x - a->x) + (c->y - a->y)*(b->y - a->y);
    if (dotproduct < 0)
    {
        return false;
    }
    float squaredlengthba = (b->x - a->x)*(b->x - a->x) + (b->y - a->y)*(b->y - a->y);
    if (dotproduct > squaredlengthba)
    {
        return false;
    }
    return true;
}*/

/*bool onSegment(point p, point q, point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
    {
        return true;
    }
    return false;
}

int orientation(point a, point b, point c)
{
    float val = (b.y - a.y)*(c.x - b.x) -
              (b.x - a.x)*(c.y - b.y);
    if (abs(val) < epsilon)
    {
        return 0;
    }
    return (val > epsilon)? 1:2;
}

bool doIntersect(point p1, point q1, point p2, point q2)
{
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
    {
        return true;
    }

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
    return false;
}*/
int main(int argc, char const *argv[])
{
    point intersectioned;
    float a;
    float b;
    float c; 
    float d;
    ifstream infile("lines.txt");
    ifstream infile2("rect.txt");
    float rectx1;
    float rectx2;
    float recty1;
    float recty2;
    int i = 0;
    point array[100][2];
    while (infile >> a >> b >> c >> d)
    {
        array[i][0] = {float(a), float(c)};
        array[i][1] = {float(b), float(d)};
        i += 1;        
    }
    infile2 >> rectx1 >> recty1 >> rectx2 >> recty2;
    point arrayintersect[1000];
    int l = 0;
    for (int k = 0; k<i; k++)
    {
        for(int j = 0; j < i; j++)
        {
            if(k == j)
            {
                continue;
            }
            else
            {
                point intersect = lineIntersection(array[k][0],array[k][1],
                    array[j][0],array[j][1]);
                int flag = 0;
                for (int p = 0; p<=l; p++)
                {
                    if(intersect.x == arrayintersect[p].x && intersect.y == arrayintersect[p].y)
                    {
                        flag = 1;
                    }
                }
                if (flag == 1)
                {
                    continue;
                }
                else if(intersect.x != FLT_MAX && intersect.y != FLT_MAX)
                {
                    arrayintersect[l] = intersect;
                    l += 1;
                }
            }
        }
    }

    //for (int j = 0; j<l;j++)
    //{
    //    cout << arrayintersect[j].x << ' ' << arrayintersect[j].y << endl;
    //}
    //cout << "Number of intersections: " << count << '\n';
    //point inter = lineIntersection(array[0][0],array[0][1],array[1][0],array[1][1]);
    //cout << inter.x << " " << inter.y;
    //point intersections_in_rectangle[100];
    int count = 0;
    cout << endl << "Intersections within the rectangle:" << endl;
    for(int j = 0; j < l; j++)
    {
        if(arrayintersect[j].x <= max(rectx2,rectx1) && arrayintersect[j].x >= min(rectx1,rectx2)
            && arrayintersect[j].y <= max(recty2,recty1) && arrayintersect[j].y >= min(recty2,recty1))
        {
            cout << arrayintersect[j].x << " " << arrayintersect[j].y << endl; 
            count += 1;
        }
    }
    cout << "Number of intersections in the rectangle: " << count << endl;
    return 0;
}