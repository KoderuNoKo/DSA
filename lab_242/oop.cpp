#include<math.h>
#include<iostream>

using namespace std;

class Point
{
private:
    double x, y;

public:
    Point()
    {
        /*  
         * STUDENT ANSWER   
         * TODO: set zero x-y coordinate
         */
        this->x = 0;
        this->y = 0;
    }

    Point(double x, double y)
    {
        /*  
         * STUDENT ANSWER
         */
        this->x = x;
        this->y = y;
    }

    void setX(double x)
    {
        /*  
         * STUDENT ANSWER
         */
        this->x = x;
    }

    void setY(double y)
    {
        /*  
         * STUDENT ANSWER
         */
        this->y = y;
    }

    double getX() const
    {
        /*  
         * STUDENT ANSWER
         */
        return this->x;
    }

    double getY() const
    {
        /*  
         * STUDENT ANSWER
         */
        return this->y;
    }

    double distanceToPoint(const Point& pointA)
    {
        /*  
         * STUDENT ANSWER   
         * TODO: calculate the distance from this point to point A in the coordinate plane
         */
        return sqrt(pow(x - pointA.x, 2) + pow(y - pointA.y, 2));
    }
};

class Circle
{
private:
    Point center;
    double radius;

public:
    Circle()
    {
        /*  
         * STUDENT ANSWER   
         * TODO: set zero center's x-y and radius
         */
        this->center = Point();
        this->radius = 0;
    }

    Circle(Point center, double radius)
    {
        /*  
         * STUDENT ANSWER
         */
        this->center = center;
        this->radius = radius;
    }

    Circle(const Circle &circle)
    {
        /*  
         * STUDENT ANSWER
         */
        this->center = circle.getCenter();

    }
    
    void setCenter(Point point)
    {
        /*  
         * STUDENT ANSWER
         */
    }

    void setRadius(double radius)
    {
        /*  
         * STUDENT ANSWER
         */
    }

    Point getCenter() const
    {
        /*  
         * STUDENT ANSWER
         */
    }

    double getRadius() const
    {
        /*  
         * STUDENT ANSWER
         */
    }
    
    void printCircle()
    {
        printf("Center: {%.2f, %.2f} and Radius %.2f\n", this->center.getX(), this->center.getY(), this->radius);
    }
};

class Character {
    protected:
        int hp;
        int x;
        int y;
    public:
        // Constructor: set the values of x and y and hp to 0
        Character();
    
        // Constructor: set the values of hp, x and y to each parameter
        Character(int hp, int x, int y);
    
        // Set and get hp
        int getHp();
        void setHp(int hp);
    
        // Set and get x
        int getX();
        void setX(int x);
        
        // Set and get y
        int getY();
        void setY(int y);
    
        // Get Manhattan distance to other character
        int getManhattanDistTo(Character* other);
};

Character::Character() {
    // STUDENT ANSWER
    this->x = this->y = this->hp = 0;
}

Character::Character(int hp, int x, int y) {
    // STUDENT ANSWER
    this->hp = hp;
    this->x = x;
    this->y = y;
}

int Character::getHp() {
    // STUDENT ANSWER
    return this->hp;
}

void Character::setHp(int hp) {
    // STUDENT ANSWER
    this->hp = hp;
}

int Character::getX() {
    // STUDENT ANSWER
    return this->x;
}

void Character::setX(int x) {
    // STUDENT ANSWER
    this->x = x;
}

int Character::getY() {
    // STUDENT ANSWER
    return this->y;
}

void Character::setY(int y) {
    // STUDENT ANSWER
    this->y = y;
}

int Character::getManhattanDistTo(Character* other) {
    // STUDENT ANSWER
    return abs(this->x - other->x) + abs(this->y - other->y);
}

class Book
{
private:
    char* title;
    char* authors;
    int publishingYear;

public:
    Book()
    {
        /*
         * STUDENT ANSWER
         * TODO: set zero publishingYear and null pointer
         */
         this->publishingYear = 0;
         this->authors = nullptr;
         this->title = nullptr;
    }

    Book(const char* title, const char* authors, int publishingYear)
    {
        /*
         * STUDENT ANSWER
         */
        this->publishingYear = publishingYear;
        this->authors = new char[strlen(authors) + 1];
        strcpy(this->authors, authors);
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
    }

    Book(const Book &book)
    {
        /*
         * STUDENT ANSWER
         * TODO: deep copy constructor
         */
        this->publishingYear = book.publishingYear;
        this->authors = new char[strlen(book.authors) + 1];
        strcpy(this->authors, book.authors);
        this->title = new char[strlen(book.title) + 1];
        strcpy(this->title, book.title);
    }
    
    void setTitle(const char* title)
    {
        /*
         * STUDENT ANSWER
         */
        delete[] this->title;
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
    }

    void setAuthors(const char* authors)
    {
        /*
         * STUDENT ANSWER
         */
        delete[] this->authors;
        this->authors = new char[strlen(authors) + 1];
        strcpy(this->authors, authors);
    }

    void setPublishingYear(int publishingYear)
    {
        /*
         * STUDENT ANSWER
         */
        this->publishingYear = publishingYear;
    }

    char* getTitle() const
    {
        /*
         * STUDENT ANSWER
         */
        char* ret = new char[strlen(this->title) + 1];
        strcpy(ret, this->title);
        return ret;
    }

    char* getAuthors() const
    {
        /*
         * STUDENT ANSWER
         */
        char* ret = new char[strlen(this->authors) + 1];
        strcpy(ret, this->authors);
        return ret;
    }

    int getPublishingYear() const
    {
        /*
         * STUDENT ANSWER
         */
        return this->publishingYear;
    }

    ~Book()
    {
        /*
         * STUDENT ANSWER
         */
        delete[] title;
        delete[] authors;
    }

    void printBook(){
        printf("%s\n%s\n%d", this->title, this->authors, this->publishingYear);
    }
};

enum Color
{
    red,
    green,
    blue
};
enum Size
{
    small,
    medium,
    big
};

class Toy
{
protected:
    double price;

public:
    Toy(double price)
    {
        this->price = price;
    }

    virtual void printType() = 0;
    friend class ToyBox;
};

class CarToy : public Toy
{
private:
    Color color;

public:
    CarToy(double price, Color color) : Toy(price), color(color)
    {
        /*
         * STUDENT ANSWER
         */
    }

    void printType()
    {
        cout << "This is a car toy\n";
    }

    friend class ToyBox;
};

class PuzzleToy : public Toy
{
private:
    Size size;

public:
    PuzzleToy(double price, Size size) : Toy(price), size(size)
    {
        /*
         * STUDENT ANSWER
         */
    }

    void printType()
    {
        cout << "This is a puzzle toy\n";
    }

    friend class ToyBox;
};

class ToyBox
{
private:
    Toy* toyBox[5];
    int numberOfItems;

public:
    ToyBox() : toyBox(), numberOfItems(0)
    {
        /*
         * STUDENT ANSWER
         * TODO: set zero numberOfItems and nullptr toyBox
         */
    }
    
    int addItem(const CarToy& carToy)
    {
        /*
         * STUDENT ANSWER
         * TODO: function add a new Car toy to the box.
                 If successfully added, the function returns the current number of toys in the box. 
                 If the box is full, return -1.
         */
        if (numberOfItems == 5) {
            return -1;
        }
        toyBox[numberOfItems] = new CarToy(carToy);
        return ++numberOfItems;
    }
    
    int addItem(const PuzzleToy& puzzleToy)
    {
        /*
         * STUDENT ANSWER
         * TODO: function add a new Puzzle toy to the box.
                 If successfully added, the function returns the current number of toys in the box. 
                 If the box is full, return -1.
         */
        if (numberOfItems == 5) {
            return -1;
        }
        toyBox[numberOfItems++] = new PuzzleToy(puzzleToy);
        return numberOfItems;
    }
    
    void printBox()
    {
        for (int i = 0; i < numberOfItems; i++)
            toyBox[i]->printType();
    }
};