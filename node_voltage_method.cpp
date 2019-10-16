#include<iostream>
using namespace std;
int main()
{
    int R_matrix[10][3]={0};//保存电阻信息的矩阵，其中依次为 节点1，节点2， 电阻值
    int I_matrix[10][3]={0};//保电流源信息的矩阵，其中依次为 节点1，节点2， 电流值
    cout<<"请输入电路中元件的个数"<<endl;
    int num;
    cin>>num;
    cout<<"请输入节点数"<<endl;
    int node;
    cin>>node;
    cout<<"请输入电路中的电阻/独立电流源所在的两端节点以及电阻/电流大小"<<endl;
    char flag;//元件类型
    int node1,node2;//元件两端节点
    int R;//电阻值 
    int I;//电流值
    int m=0;//电阻个数
    int n=0;//电流源个数

    //输入部分
    for(int i=0;i<num;i++)
    {
        cin>>flag;
        if(flag=='R')//输入是电阻
        {
            cin>>node1>>node2>>R;
            R_matrix[m][0]=node1;
            R_matrix[m][1]=node2;
            R_matrix[m][2]=R;
            m++;
        }
        if(flag=='I')//输入是电流源
        {
            cin>>node1>>node2>>I;
            I_matrix[n][0]=node1;
            I_matrix[n][1]=node2;
            I_matrix[n][2]=I;
            n++;
        }
    }
  
   /*
    test
    {
        
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<3;j++)
                cout<<R_matrix[i][j]<<" ";
            cout<<endl;
        }    
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<3;j++)
                cout<<I_matrix[i][j]<<" ";
            cout<<endl;
        }  
    }
  */

    //初始化关系矩阵
    int relation[10][10]={0};
    for(int i=1;i<=node;i++)
        for(int j=1;j<=node;j++)
            {
                if(i==j) relation[i][j]=1;
                else relation[i][j]=-1;
            }

    /*
        test
        for(int i=0;i<node;i++)
        {
            for(int j=0;j<node;j++)
            cout<<relation[i][j]<<" "; 
            cout<<endl;
        }
    */
    //生成电导矩阵
    double G_matrix[10][10]={0.0};
    for(int i=1;i<=node;i++)//对于第i个节点
    {
        for(int a=0;a<m;a++)//遍历每个电阻
        {
            if(R_matrix[a][0]==i)//左端连着第i个节点
            {
                //求自导
                G_matrix[i][i]+=(1/((double)R_matrix[a][2]))*relation[i][i];
                //求互导
                int j=R_matrix[a][1];
                if(j!=0)
                {
                    G_matrix[i][j]+=(1/((double)R_matrix[a][2]))*relation[i][j];
                }
            }
            if(R_matrix[a][1]==i)//右端连着第i个节点
             {
                //求自导
                G_matrix[i][i]+=(1/((double)R_matrix[a][2]))*relation[i][i];
                //求互导
                int j=R_matrix[a][0];
                if(j!=0)
                {
                    G_matrix[i][j]+=(1/((double)R_matrix[a][2]))*relation[i][j];
                }
            }
        }
    }
    /*  
        test
        for(int i=1;i<=node;i++)
        {
            for(int j=1;j<=node;j++)
            cout<<G_matrix[i][j]<<" "; 
            cout<<endl;
        }
    */
    return 0;
}