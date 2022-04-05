#ifndef ACTION_GRAPH_H
#define ACTION_GRAPH_H
#include<QObject>

class Action_Graph: public QObject
{
    Q_OBJECT
public:
    /*Hide and Show Graph&Legend*/
    void Hide_And_Show_All_Graph();
    void Hide_And_Show_P1_Graph();
    void Hide_And_Show_P2_Graph();
    void Hide_And_Show_T1_Graph();
    void Hide_And_Show_T2_Graph();
    void Hide_And_Show_P1O_Graph();
    void Hide_And_Show_P2O_Graph();
    void Hide_And_Show_T1O_Graph();
    void Hide_And_Show_T2O_Graph();
    void Hide_And_Show_Ext_Graph();
    void Hide_And_Show_A1_Graph();
    void Hide_And_Show_Gp_Graph();
    void Hide_And_Show_A2_Graph();
    void Hide_And_Show_ExtO_Graph();
    void Hide_And_Show_A1O_Graph();
    void Hide_And_Show_GpO_Graph();
    void Hide_And_Show_A2O_Graph();
    /*Hide and Show Graph&Legend*/

};

#endif // ACTION_GRAPH_H
