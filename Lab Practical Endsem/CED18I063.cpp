#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdlib.h>
using namespace std;
#define PI 3.1415926535
#define maxHt 600
#define maxWd 480
#define maxVer 10000
typedef struct edgebucket
{
    int ymax; //max y-coordinate of edge
    float xofymin; //x-coordinate of lowest edge point updated only in aet
    float slopeinverse;
} EdgeBucket;
typedef struct edgetabletup
{
    int countEdgeBucket; //no. of edgebuckets
    EdgeBucket buckets[maxVer];
} EdgeTableTuple;
EdgeTableTuple EdgeTable[maxHt], ActiveEdgeTuple;
// Scanline Function
void initEdgeTable()
{
    int i;
    for (i = 0; i < maxHt; i++)
    {
        EdgeTable[i].countEdgeBucket = 0;
    }
    ActiveEdgeTuple.countEdgeBucket = 0;
}
/* Function to sort an array using insertion sort*/
void insertionSort(EdgeTableTuple *ett)
{
    int i, j;
    EdgeBucket temp;
    for (i = 1; i < ett->countEdgeBucket; i++)
    {
        temp.ymax = ett->buckets[i].ymax;
        temp.xofymin = ett->buckets[i].xofymin;
        temp.slopeinverse = ett->buckets[i].slopeinverse;
        j = i - 1;
        while ((temp.xofymin < ett->buckets[j].xofymin) && (j >= 0))
        {
            ett->buckets[j + 1].ymax = ett->buckets[j].ymax;
            ett->buckets[j + 1].xofymin = ett->buckets[j].xofymin;
            ett->buckets[j + 1].slopeinverse = ett->buckets[j].slopeinverse;
            j = j - 1;
        }
        ett->buckets[j + 1].ymax = temp.ymax;
        ett->buckets[j + 1].xofymin = temp.xofymin;
        ett->buckets[j + 1].slopeinverse = temp.slopeinverse;
    }
}
void storeEdgeInTuple (EdgeTableTuple *receiver, int ym, int xm, float slopInv)
{
    (receiver->buckets[(receiver)->countEdgeBucket]).ymax = ym;
    (receiver->buckets[(receiver)->countEdgeBucket]).xofymin = (float)xm;
    (receiver->buckets[(receiver)->countEdgeBucket]).slopeinverse = slopInv;
    // sort the buckets
    insertionSort(receiver);
    (receiver->countEdgeBucket)++;
}
void storeEdgeInTable (int x1, int y1, int x2, int y2)
{
    float m, minv;
    int ymaxTS, xwithyminTS, scanline; //ts stands for to store
    if (x2 == x1)
    {
        minv = 0.000000;
    }
    else
    {
        m = ((float)(y2 - y1)) / ((float)(x2 - x1));
        // horizontal lines are not stored in edge table
        if (y2 == y1)
            return;
        minv = (float)1.0 / m;
    }
    if (y1 > y2)
    {
        scanline = y2;
        ymaxTS = y1;
        xwithyminTS = x2;
    }
    else
    {
        scanline = y1;
        ymaxTS = y2;
        xwithyminTS = x1;
    }
    storeEdgeInTuple(&EdgeTable[scanline], ymaxTS, xwithyminTS, minv);
}
void removeEdgeByYmax(EdgeTableTuple *Tup, int yy)
{
    int i, j;
    for (i = 0; i < Tup->countEdgeBucket; i++)
    {
        if (Tup->buckets[i].ymax == yy)
        {
            for ( j = i ; j < Tup->countEdgeBucket - 1 ; j++ )
            {
                Tup->buckets[j].ymax = Tup->buckets[j + 1].ymax;
                Tup->buckets[j].xofymin = Tup->buckets[j + 1].xofymin;
                Tup->buckets[j].slopeinverse = Tup->buckets[j + 1].slopeinverse;
            }
            Tup->countEdgeBucket--;
            i--;
        }
    }
}
void updatexbyslopeinv(EdgeTableTuple *Tup)
{
    int i;
    for (i = 0; i < Tup->countEdgeBucket; i++)
    {
        (Tup->buckets[i]).xofymin = (Tup->buckets[i]).xofymin + (Tup->buckets[i]).slopeinverse;
    }
}
void ScanlineFill()
{
    int i, j, x1, ymax1, x2, ymax2, FillFlag = 0, coordCount;
    // we will start from scanline 0;
    // Repeat until last scanline:
    for (i = 0; i < maxHt; i++) //4. Increment y by 1 (next scan line)
    {
        // 1. Move from ET bucket y to the
        // AET those edges whose ymin = y (entering edges)
        for (j = 0; j < EdgeTable[i].countEdgeBucket; j++)
        {
            storeEdgeInTuple(&ActiveEdgeTuple, EdgeTable[i].buckets[j].
                             ymax, EdgeTable[i].buckets[j].xofymin,
                             EdgeTable[i].buckets[j].slopeinverse);
        }
        // 2. Remove from AET those edges for
        // which y=ymax (not involved in next scan line)
        removeEdgeByYmax(&ActiveEdgeTuple, i);
        //sort AET (remember: ET is presorted)
        insertionSort(&ActiveEdgeTuple);
        //3. Fill lines on scan line y by using pairs of x-coords from AET
        j = 0;
        FillFlag = 0;
        coordCount = 0;
        x1 = 0;
        x2 = 0;
        ymax1 = 0;
        ymax2 = 0;
        while (j < ActiveEdgeTuple.countEdgeBucket)
        {
            if (coordCount % 2 == 0)
            {
                x1 = (int)(ActiveEdgeTuple.buckets[j].xofymin);
                ymax1 = ActiveEdgeTuple.buckets[j].ymax;
                if (x1 == x2)
                {
                    if (((x1 == ymax1) && (x2 != ymax2)) || ((x1 != ymax1) && (x2 == ymax2)))
                    {
                        x2 = x1;
                        ymax2 = ymax1;
                    }
                    else
                    {
                        coordCount++;
                    }
                }
                else
                {
                    coordCount++;
                }
            }
            else
            {
                x2 = (int)ActiveEdgeTuple.buckets[j].xofymin;
                ymax2 = ActiveEdgeTuple.buckets[j].ymax;
                FillFlag = 0;
                // checking for intersection...
                if (x1 == x2)
                {
                    if (((x1 == ymax1) && (x2 != ymax2)) || ((x1 != ymax1) && (x2 == ymax2)))
                    {
                        x1 = x2;
                        ymax1 = ymax2;
                    }
                    else
                    {
                        coordCount++;
                        FillFlag = 1;
                    }
                }
                else
                {
                    coordCount++;
                    FillFlag = 1;
                }
                if (FillFlag)
                {
                    //drawing actual lines...
                    glColor3f(0.0f, 0.7f, 0.0f);
                    glBegin(GL_LINES);
                    glVertex2i(x1, i);
                    glVertex2i(x2, i);
                    glEnd();
                    glFlush();
                }
            }
            j++;
        }
        // 5. For each nonvertical edge remaining in AET, update x for new y
        updatexbyslopeinv(&ActiveEdgeTuple);
    }
}

pair<int,int> traslate_and_rotate(int a,int b,int r, int the)
{
    double theta = the * PI / 180.0;
    double cosine = cos(theta);
    double sine = sin(theta);
    double m = -(cosine/sine);
    double c = r/sine;
    b=b-c;
    double angle = atan(m);
    a=a*cos(-angle)-b*sin(-angle);
    b=a*sin(-angle)+b*cos(-angle);
    b=-b;
    a=a*cos(angle)-b*sin(angle);
    b=a*sin(angle)+b*cos(angle);
    b=b+c;
    pair<int,int> ans;
    ans.first=a;
    ans.second=b;
    return ans;
}

void drawPoly()
{
    pair<int,int> ans;
    int r = 10;
    int the = 90;
    glColor3f(1.0f, 0.0f, 0.0f);
    int count = 0, x1, y1, x2, y2;
    int x[] = {-200,-100,-100,-200,-200};
    int y[] = {300,300,0,0,300};
    int i = 0;
    while (i < 4)
    {
        x1 = x[i];
        x2 = x[i + 1];
        y1 = y[i];
        y2 = y[i + 1];
        glBegin(GL_LINES);
        glVertex2i( x1, y1);
        glVertex2i( x2, y2);
        glEnd();
        storeEdgeInTable(x1, y1, x2, y2);//storage of edges in edge table.
        i++;
    }
    

    glColor3f(1.0f, 0.0f, 0.0f);
    count = 0;
    int x_[] = {0,100,200,100,0};
    int y_[] = {300,300,0,0,300};
    i = 0;
    while (i < 4)
    {
        x1 = x_[i];
        x2 = x_[i + 1];
        y1 = y_[i];
        y2 = y_[i + 1];
        glBegin(GL_LINES);
        glVertex2i( x1, y1);
        glVertex2i( x2, y2);
        glEnd();
        storeEdgeInTable(x1, y1, x2, y2);//storage of edges in edge table.
        i++;
    }
    

    glColor3f(1.0f, 0.0f, 0.0f);
    count = 0;
    int x__[] = {350,450,300,200,350};
    int y__[] = {300,300,0,0,300};
    i = 0;
    while (i < 4)
    {
        x1 = x__[i];
        x2 = x__[i + 1];
        y1 = y__[i];
        y2 = y__[i + 1];
        glBegin(GL_LINES);
        glVertex2i( x1, y1);
        glVertex2i( x2, y2);
        glEnd();
        storeEdgeInTable(x1, y1, x2, y2);//storage of edges in edge table.
        i++;
    }
}
void display(void)
{
    initEdgeTable();
    drawPoly();
    ScanlineFill();//actual calling of scanline filling..
}
void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-maxHt, maxHt, -maxWd, maxWd);
    glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(maxHt, maxWd);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Scanline fill");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
