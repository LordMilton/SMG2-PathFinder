//Represents as an individual level
class Star
{	private:
	String name;
	int time;
	int timeWithMedal;
	
	public:
	Star(String name)
	{
		this.name = name;
		time = 600;
		timeWithMedal = 600;
	}
	
	void setTime(int time)
	{
		this.time = time;
	}
	
	void setTimeWithMedal(int time)
	{
		timeWithMedal = time;
	}
	
	String getName()
	{
		return name;
	}
	
	int getTime()
	{
		return time;
	}
	
	int getTimeWithMedal()
	{
		return getTimeWithMedal;
	}
};