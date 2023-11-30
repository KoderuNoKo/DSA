#include <iostream>

using namespace std;

class Point
{
private:
    double x, y;

public:
    Point()
    {
        x = 0;
        y = 0;
    }

    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    void setX(double x) { this->x = x; }

    void setY(double y) { this->y = y; }

    double getX() const { return x; }

    double getY() const { return y; }

    double distanceToPoint(const Point& pointA) {
        return sqrt((x - pointA.getX()) * (x - pointA.getX()) + (y - pointA.getY()) * (y - pointA.getY()));
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
        center.setX(0);
        center.setY(0);
        radius = 0;
    }

    Circle(Point center, double radius)
    {
        setCenter(center);
        setRadius(radius);
    }

    Circle(const Circle& circle)
    {
        setCenter(circle.getCenter());
        setRadius(circle.getRadius());
    }

    void setCenter(Point point)
    {
        this->center.setX(point.getX());
        this->center.setY(point.getY());
    }

    void setRadius(double radius)
    {
        if (radius > 0) this->radius = radius;
        else
            radius = 0;
    }

    Point getCenter() const { return this->center; }

    double getRadius() const { return this->radius; }

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
    x = y = hp = 0;
}

Character::Character(int hp, int x, int y) {
    // STUDENT ANSWER
    setHp(hp);
    setX(x);
    setY(y);
}

int Character::getHp() { 
    // STUDENT ANSWER
    return hp;
}

void Character::setHp(int hp) {
    // STUDENT ANSWER
    this->hp = hp;
}

int Character::getX() {
    // STUDENT ANSWER
    return x;
}

void Character::setX(int x) {
    // STUDENT ANSWER
    this->x = x;
}

int Character::getY() {
    // STUDENT ANSWER
    return y;
}

void Character::setY(int y) {
    // STUDENT ANSWER
    this->y = y;
}

int Character::getManhattanDistTo(Character* other) {
    // STUDENT ANSWER
    return abs(x - other->getX()) + abs(y - other->getY());
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
        title = nullptr;
        authors = nullptr;
        publishingYear = 0;
    }

    Book(const char* title, const char* authors, int publishingYear)
    {
        this->title = new char[strlen(title) + 1];
        //strcpy(this->title, title);
        this->authors = new char[strlen(authors) + 1];
        //strcpy(this->authors, authors);
        this->publishingYear = publishingYear;
    }

    Book(const Book& book)
    {
        title = new char[strlen(book.title) + 1];
        //strcpy(title, book.title);
        authors = new char[strlen(book.authors) + 1];
        //strcpy(authors, book.authors);
        publishingYear = book.publishingYear;
    }

    void setTitle(const char* title)
    {
        delete[] this->title;
        this->title = new char[strlen(title) + 1];
        //strcpy(this->title, title);
    }

    void setAuthors(const char* authors)
    {
        delete[] this->authors;
        this->authors = new char[strlen(authors) + 1];
        //strcpy(this->authors, authors);
    }

    void setPublishingYear(int publishingYear)
    {
        this->publishingYear = publishingYear;
    }

    char* getTitle() const
    {
        return title;
    }

    char* getAuthors() const
    {
        return authors;
    }

    int getPublishingYear() const
    {
        return publishingYear;
    }

    ~Book()
    {
        delete[] title;
        delete[] authors;
    }

    void printBook() {
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
    CarToy(double price, Color color) : Toy(price)
    {
        this->color = color;
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
    PuzzleToy(double price, Size size) : Toy(price)
    {
        this->size = size;
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
    ToyBox() 
    {
        /*
         * STUDENT ANSWER
         * TODO: set zero numberOfItems and nullptr toyBox
         */
        for (auto& item : toyBox) {
            item = nullptr;
        }
        numberOfItems = 0;
    }

    int addItem(const CarToy& carToy)
    {
        /*
         * STUDENT ANSWER
         * TODO: function add a new Car toy to the box.
                 If successfully added, the function returns the current number of toys in the box.
                 If the box is full, return -1.
         */
        if (numberOfItems < 5) {
            toyBox[numberOfItems] = new CarToy(carToy);
            return ++numberOfItems;
        }
        return -1;
    }

    int addItem(const PuzzleToy& puzzleToy)
    {
        /*
         * STUDENT ANSWER
         * TODO: function add a new Puzzle toy to the box.
                 If successfully added, the function returns the current number of toys in the box.
                 If the box is full, return -1.
         */
        if (numberOfItems < 5) {
            toyBox[numberOfItems] = new PuzzleToy(puzzleToy);
            return ++numberOfItems;
        }
        return -1;
    }

    void printBox()
    {
        for (int i = 0; i < numberOfItems; i++)
            toyBox[i]->printType();
    }
};