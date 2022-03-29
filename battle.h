#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED

#include <time.h>
#include <stdlib.h>
#include <vector>
using namespace std;


class BattleMap
{
public:
    BattleMap(int row = 10, int col = 10)
    {
        r = row;
        c = col;
        vector <vector<int> > Map(r, vector<int>(c));
        m = Map;
        vector <vector<bool> > Flag(r, vector<bool>(c));
        flag = Flag;

    }
    int getrow(){return r;}const
    int getcol(){return c;}const
    bool isvalid(int x, int y){return x < r && y < c && m[x][y] == 0;}              //���õ��Ƿ���ԷŴ�
    bool isempty(int x, int y){return m[x][y] == 0;}                                //���õ��Ƿ�û�д�����ȷ���Ϸ���
    bool isvalid(int x, int y, int length, bool direction);                         //���ó����Ƿ���ԷŴ�
    int getkind(int x, int y){return m[x][y];}                                      //��ȡ�������ࣨ�����ô��ĳ�������������
    void showBM(void);                                                              //���ڿ���̨��ʾ
    bool put(int x, int y, int kind);                                               //�ڸõ�Ŵ�
    bool isvalid(int x, int y, int m, int n, bool direction);
    bool put(int x, int y, int length, bool direction, int kind);		            //�ڸõ��λ�÷��붨����������Ĵ�
    void randput(int m, int n, int kind);                                           //�������ָ�����ȵĴ�
    void randmap(void);                                                             //���������ͼ
    void check(int x, int y){flag[x][y] = 1;}                                       //���õ��Ƿ��д�
    bool ischecked(int x, int y){return flag[x][y];}                                //���õ��Ƿ񱻼���
    bool isfinished(void);                                                          //�ж���Ӯ
    void ClearMap(void);                                                            //��յ�ͼ
    bool put(int x, int y, int m, int n, bool direction, int kind);
private:
    vector<vector<int> > m;
    vector<vector<bool> > flag;
    int r;
    int c;
};

void BattleMap::showBM(void)
{
    for(int i = 0; i < r; i ++)
    {
        for(int j = 0; j < c; j++)
            cout<<m[i][j]<<' ';
            cout<<endl;
    }
}
bool BattleMap::isvalid(int x, int y, int length, bool direction)//x,y = ��ʼ���꣬ length = ս�����ȣ� direction:0:����1������
{
        for(int i = 0; i < length; i ++)
        {
            if(direction)//
                if(!isvalid(x + i, y))
                    return 0;
            if(!direction)//
                if(!isvalid(x, y + i))
                    return 0;
        }
        return 1;
}
bool BattleMap::isvalid(int x, int y, int m, int n, bool direction)
{
	for(int i = 0; i < m; i ++)
		for(int j = 0; j < n; j++)
		{
			if(direction)
				if(!isvalid(x + i,y + j))
					return 0;
			if(!direction)
				if(!isvalid(x + j,y + i))
					return 0;
		}
	return 1;
}
bool BattleMap::put(int x, int y, int kind)
{
    if(isvalid(x, y)){
    	m[x][y] = kind;
    	return 1;
	}
	else return 0;

}
bool BattleMap::put(int x, int y, int length, bool direction, int kind)//x,y = ��ʼ���꣬ length = ս�����ȣ� direction:0:����1������
{
	if(kind == -1) kind = length;
	if(isvalid(x, y, length, direction))
	{
		for(int i = 0; i < length; i ++)
		{
			if(!direction)
				put(x, y + i, kind);
			if(direction)
				put(x + i, y, kind);
		}
		return 1;
	}
	else return 0;
}
void BattleMap::randput(int m, int n, int kind)
{
    //srand(time(NULL));
    if(kind == -1) kind = m * n;
	int direction;
	while(1){
	direction = rand()%2;
    if(put(rand()%r, rand()%c, m, n, (bool)direction, kind))
    	return;}
}
void BattleMap::randmap(void)
{
	ClearMap();
	randput(3,2,-1);
	for(int i = 0; i < 2; i++){
		randput(1,2,-1);
		randput(2,2,-1);
	}
	for(int i = 0; i < 4; i++){
		randput(1,1,-1);
	}

}
bool BattleMap::isfinished(void)
{
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            if(!isempty(i,j))
                if(!ischecked(i,j))
                    return 0;
    return 1;
}
void BattleMap::ClearMap(void)
{
        for(int i = 0; i < r; i++)
            for(int j = 0; j < c ; j ++)
            {
                m[i][j] = 0;
                flag[i][j] = 0;
            }
}
bool BattleMap::put(int x, int y, int m, int n, bool direction, int kind)
{
	if(isvalid(x,y,m,n,direction)){
	if(kind == -1) kind = m * n;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				put(x + i,y + j,kind);
		return 1;
	}
	else return 0;
}
#endif // BATTLE_H_INCLUDED
