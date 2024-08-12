#include <iostream>
#include <vector>
#include <string>
#include <random>

class item {
    public:
        int type;
        int usePrecent;
};

item Rock;
item Paper;
item Scissors;

int againstEffective;
int againstItself;
int againstEnemy;

class object {
public:
    item Item;
    int Food;
};

std::vector <object> Humans;

int population;
int populationToAdd;
int populationToRemove;
int generations;

void ItemSet()
{
    Rock.type = 4;
    Paper.type = 2;
    Scissors.type = 3;

    Rock.usePrecent = 0;
    Paper.usePrecent = 0;
    Scissors.usePrecent = 0;
}

void FillPopulation()
{
    for (int i = 0; i < population; i++)
    {
        object Human;
            
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1,3);
        
        switch (dist6(rng))
        {
        case 1:
            Human.Item = Rock;
            Human.Item.type = 4;
            break;
        case 2:
            Human.Item = Paper;
            Human.Item.type = 2;
            break;
        case 3:
            Human.Item = Scissors;
            Human.Item.type = 3;
            break;
        }

        Human.Food = 0;

        Humans.push_back(Human);
    }
    
}



void FillPopulationEqual()
{
    int item = 1;
    for (int i = 0; i < population; i++)
    {
        object Human;

        switch (item)
        {
        case 1:
            Human.Item = Rock;
            Human.Item.type = 4;
            break;
        case 2:
            Human.Item = Paper;
            Human.Item.type = 2;
            break;
        case 3:
            Human.Item = Scissors;
            Human.Item.type = 3;
            break;
        }

        Human.Food = 0;

        Humans.push_back(Human);
        item += 1;
        if(item > 3)
        {
            item = 1;
        }
     //   std::cout << item << std::endl;
    }
}

void Reproduce(object human, int item, int number)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 3);
    
    if (human.Food > 1)
    {
        object Human;

        switch (item)
        {
            case 1:
                Human.Item = Rock;
                Human.Item.type = 4;
                break;
            case 2:
                Human.Item = Paper;
                Human.Item.type = 2;
                break;
            case 3:
                Human.Item = Scissors;
                Human.Item.type = 3;
                break;
        }

        Human.Food = 0;

        Humans.push_back(Human);
        populationToAdd += 1;
    }
    else {
        object Human;

        switch (item)
        {
        case 1:
            Human.Item = Rock;
            Human.Item.type = 4;
            break;
        case 2:
            Human.Item = Paper;
            Human.Item.type = 2;
            break;
        case 3:
            Human.Item = Scissors;
            Human.Item.type = 3;
            break;
        }

        Human.Food = 0;
        populationToAdd += 1;

        Humans.push_back(Human);
        
    } 
    if (human.Food == 0)
    {
        Humans.erase(Humans.begin() + number);
        populationToRemove += 1;
    }

}

void ChangeItem(object human)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 3);

    switch (dist(rng))
    {
    case 1:
        human.Item = Rock;
        human.Item.type = 4;
        break;
    case 2:
        human.Item = Paper;
        human.Item.type = 2;
        break;
    case 3:
        human.Item = Scissors;
        human.Item.type = 3;
        break;
    }
}

void Encounter(object human1,object human2, int number)
{
    if (human1.Item.type == human2.Item.type)
    {
        human1.Food += 1;
        human2.Food += 1;
        ChangeItem(human1);
        ChangeItem(human2);

        if (human1.Item.type == 2)
        {
            Paper.usePrecent += 1;
        }
        if (human1.Item.type == 3)
        {
            Scissors.usePrecent += 1;
        }
        if (human1.Item.type == 4)
        {
            Rock.usePrecent += 1;
        }

    }
    if (human1.Item.type < human2.Item.type)
    {
        //2 albo 3
        if (human1.Item.type > 2)
        {
            //3 vs 4
            human2.Food += 2;
            ChangeItem(human1);
            Rock.usePrecent += 1;
            
        }
        else {
             //2 vs 4 albo 2 vs 3
            if (human2.Item.type == 3)
            {
                //2 vs 3
                human2.Food += 2;
                ChangeItem(human1);
                Scissors.usePrecent += 1;
            }
            else {
                //2 vs 4
                human1.Food += 2;
                ChangeItem(human2);
                Paper.usePrecent += 1;
            }
        }
    }
    else {
        //3 albo 4
        if (human1.Item.type > 3)
        {
            //4 vs 3 albo 4 vs 2
            if (human2.Item.type == 3)
            {
                //4 vs 3
                human2.Food += 2;
                ChangeItem(human1);
                Rock.usePrecent += 1;
            }
            else {
                //4 vs 2
                human1.Food += 2;
                ChangeItem(human2);
                Paper.usePrecent += 1;
            }
        }
        else {
            //3 vs 2
            human2.Food += 2;
            ChangeItem(human1);
            Scissors.usePrecent += 1;
        }
    }

    Reproduce(human1, human1.Item.type, number);
    Reproduce(human2, human2.Item.type, number);


}

void StartSimulation()
{
    for (int i = 0; i < generations; i++)
    {
        if (population % 2 == 0)
        {
            //populacja jest parzysta

            for (int i = 0; i < population; i++)
            {
                Encounter(Humans[i + i], Humans[i + i + 1],i);
                
            }
            population -= populationToRemove;
            population += populationToAdd;
            populationToAdd = 0;
            populationToRemove = 0;

            std::cout << "==========" << std::endl;
            std::cout << "Generacja: " << i + 1 << std::endl;
            std::cout << "Populacja: " << population << std::endl;

            std::cout << "==========" << std::endl;
            std::cout << "Rock Usage Precent: " << Rock.usePrecent << std::endl;
            std::cout << "Paper Usage Precent: " << Paper.usePrecent << std::endl;
            std::cout << "Scissors Usage Precent: " << Scissors.usePrecent << std::endl;

            std::cout << std::endl;
        }
        else {
            //populacja jest nie parzysta
            for (int i = 0; i < population-1; i++)
            {
                Encounter(Humans[i + i], Humans[i + i + 1],i);
            }

            population -= populationToRemove;
            population += populationToAdd;
            populationToAdd = 0;
            populationToRemove = 0;

            std::cout << "==========" << std::endl;
            std::cout << "Generacja: " << i + 1 << std::endl;
            std::cout << "Populacja: " << population << std::endl;

            std::cout << "==========" << std::endl;
            std::cout << "Rock Usage Precent: " << Rock.usePrecent << std::endl;
            std::cout << "Paper Usage Precent: " << Paper.usePrecent << std::endl;
            std::cout << "Scissors Usage Precent: " << Scissors.usePrecent << std::endl;
            std::cout << std::endl;
        }

    
    }
    std::cout << "Symulacja Zakonczona!";
}

int main()
{
    ItemSet();

    againstEffective = 2;
    againstItself = 1;
    againstEnemy = -1;

    population = 99;
    populationToAdd = 0;
    populationToRemove = 0;
    generations = 10;

    std::cout << "Populacja wynosi: " << population << std::endl;
    std::cout << "Zapelniam...";

    FillPopulation();
    //FillPopulationEqual();

    std::cout << "Populacja zapelniona, rozpoczynam symulacje" << std::endl;

    

    StartSimulation();

}

 
