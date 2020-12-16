#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Animal 	
{
	private:
		std::string name;
		double temp;
		double breath;
		double heart;
	
	public:
		Animal(){}
		Animal(std::string name, double temp, double breath, double heart)
		{
			setName(name);
			setTemp(temp);
			setBreath(breath);
			setHeart(heart);

		}
		virtual bool checkHealth()=0;		
		~virtual Animal(){} /**///destructor should be virtual. and should have a body {}
		//setters
		void setTemp(double t)
		{
			temp=t;
		}
		void setBreath(double b)
		{
			breath=b;

		}
		void setHeart(double h)
		{
			heart=h;
		}
		void setName(std::string n)
		{
			name=n;
		}
		
		//getters
		std::string getName ()
		{
			return name;
		}
		int getTemp()
		{
			return temp;
		}
		int getBreath()
		{
				return breath;
		}
		int getHeart()
		{
			return heart;
		}

};

class Dog:public Animal 
{
	private:
		bool is_large;

	public:
		Dog(std::string name, double temp, double breath, double heart, bool is_large):Animal(name,temp,breath,heart),is_large(large){}
		~Dog();

		bool checkHealth() 
		{
				if ((getTemp()>=38 && getTemp()<=39.2) && (getBreath()>=10 && getBreath()<=35))
				{	
					if (is_large && getHeart()>=60 && getHeart()<=100 ) 
						return true;	
					
					//if is small
					else if (!is_large && getHeart()>=100 && getHeart()<=140) /**///test !is_large is always true
						return true;
							
				}

			return false;
		}

		
};

class Cat :public Animal 
{
	public:
		Cat(std::string name, double temp, double breath, double heart):Animal(name,temp,breath,heart){}
		bool checkHealth() 
		{

			if ((38 <= getTemp() && getTemp() <= 39.2) && (16 <= getBreath() && getBreath() <= 40) && (120 <= getHeart() && getHeart()<= 140))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		~Cat();
};

class Cow :public Animal
{
	public:
		double litres;
		bool checkHealth(){

			if ((38.5 <= getTemp() && getTemp() <= 39.5) && (26 <= getBreath() && getBreath() <= 50) && (48 <= getHeart() && getHeart()<= 84) && (milk>=30))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		Cow(std::string name, double temp, double breath, double heart, double milk):Animal(name,temp,breath,heart)
		{
			milk=litres;
		}
		~Cow();

};

class Vet
{
	private:
		static Vet* instance;
		
		std::vector <Animal*> animals;
		Vet(){}
	
	public:
		//static Vet* getInstance;
		void addAnimal (Animal* animal)
		{
			animals.push_back (animal);
		}
		void showSick()
		{
			for (std:: size_t i=0;i<animals.size();i++) /**///it is better to use std::size_t or vector<Animal*>::size_type
			{
				if (animals[i]->checkHealth()==0)
				{
					cout<<"the animal that sick is: "<<animals[i]->getName()<<std::endl;

				}

			}
		}
			
		void showSickDogs()
		{

			for (std::size_t int i=0;i<animals.size();i++) // need to change the for
			{
				if (dynamic_cast<Dog*>(animals[i]) != nullptr && animals[i]->checkHealth()==false)
					cout<<"the dog that is sick is:"<<animals[i]->getName()<<std::endl;
			}
		}
		
		static Vet& getInstance();
	

};
	
	
Vet* Vet::instance=0;
Vet& Vet::getInstance() /**///FIXED bad indentation
{
	if (instance==0)
	{
		instance=new Vet;
	}
	
	return *instance ;
}


int main() {

	cout << "program start" << endl;

	Vet& vet = Vet::getInstance();



	//healthy dog
	vet.addAnimal(new Dog("dog1", 38.5, 20, 80, true));
	//not healthy dog (temp too high)
	vet.addAnimal(new Dog("dog2", 40.0, 20, 80, true));
	//not healthy dog (heart rate too little for small breed)
	vet.addAnimal(new Dog("dog3", 38.5, 20, 80, false));
	//healthy cat
	vet.addAnimal(new Cat("cat1", 38.7, 30, 130));
	//not healthy cat (breath is too high)
	vet.addAnimal(new Cat("cat2", 38.7, 42, 130));
	//healthy cow
	vet.addAnimal(new Cow("cow1", 39.0, 37, 70, 32));
	//not healthy cow (milk production too low)
	vet.addAnimal(new Cow("cow2", 39.0, 37, 70, 20));

	vet.showSick(); //should print: dog2 dog3 cat2 cow2

	vet.showSickDogs(); //should print: dog2 dog3

}



