#pragma once//保证文件只被编译一次
#include<random>
#include<vector>
#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<bitset>
#include<iomanip>
#include<regex> //正则表达式
#include<set>
#include<algorithm>
#include<stack>
#include<sstream>

using namespace std;

static string inputString = "x2+2*(x1^2+5)+x1/3";//设置一个全局静态变量存放输入的函数
set<string> variable_Number(string); //求变量数量
void Input_function(); //输入待求的函数
void Input_domain();//输入自变量的取值范围

const double PI = 3.141592653589793;//定义一个不可改变的常量值PI
const int Po_Size = 500;//种群规模
const int Ev_Algebra = 500;//进化代数
const double Ov_Probability = 0.850; //交叉概率,交叉概率用于判断两两个体是否需要交叉
const double Va_Probability = 0.050;//变异概率,变异概率用于判断任一个体是否需要变异
static int De_Variable = variable_Number(inputString).size();//函数自变量的个数,如果要进行多元函数的最值求解，直接修改自变量数个De_Variable即可
const int length1 = 24;//精确到6位小数，用24位二进制编码
const int length2 = 23;//精确到6位小数，用23位二进制编码

class X_Range //自变量取值范围类，适用于多个变量
{
private:
    double Lower;//变量的下界取值
    double Upper;//变量的上界取值
public:
    X_Range(double m_Lower, double m_Upper);//构造函数
    double GetUpper()const;//获取变量上限
    double GetLower()const;//获取变量下限
};
class Individual //定义个体类
{
private:
    vector<double> Variable;//存放变量x1,x2,x3........
    // vector<set> Variable； Variable.resize(variable_Number(inputString).size())
    double Fitness;//适应值
    double ReFitness;//适应值概率
    double SumFitness;//累加概率，为轮盘转做准备
public:
    Individual() {}//默认构造函数
    Individual(vector<double> m_Variable);//构造函数
    vector<double> GetVariable();//获取变量值
    void ChaFitness(const double m_fitness);//修改适应值
    void ChaReFitness(const double m_ReFitness);//修改适应值概率
    void ChaSumFitness(const double m_SumFitness);//修改累加概率
    double GetFitness()const;//获取适应值
    double GetReFitness()const;//获取适应值概率
    double GetSumFitness()const;//获取累加概率
};


void Initialize();//随机初始化种群，得到第一代个体
void CaculaFitness();//计算个体的适应值
void CaculaReFitness();//计算个体的适应值概率
void CalculaSumFitness();//计算累加个体概率
void seclect();//种群选择
double Scand();//随机产生0到49的随机整数
void crossing();//杂交
void variating();//变异
void genetic_algorithm();//遗传算法
