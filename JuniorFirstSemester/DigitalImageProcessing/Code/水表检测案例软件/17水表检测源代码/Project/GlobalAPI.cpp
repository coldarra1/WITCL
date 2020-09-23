
//using namespace std;

long GetMax(long *List, int length, int StartPos)
{
	int i;
	long temp;
	temp = List[StartPos];
	for (i = StartPos; i < length; i++)
	{
		if (List[i] > temp)
		{
			temp = List[i];
		}
	}
	return temp;
}
