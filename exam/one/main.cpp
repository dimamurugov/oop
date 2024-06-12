#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

class CPoint
{
public:
    double x;
    double y;
};

/*
Интерфейс объектов, способных сохранять (SaveTo) и
восстанавливать (RestoreFrom) своё состояние из/в стандартных потоков чтения/записи
В случае ошибки выбрасывают исключения runtime_error
*/
class ISerializable
{
public:
    virtual void SaveTo(std::ostream& stream) const = 0;
    virtual void RestoreFrom(std::istream& stream) = 0;
};

// std::unique_ptr<ISerializable> s = std::make_unique<Rectangle>();
// Мы создаем "умный" указатель типа Rectangle который включает в себя ISerializable, но ISerializable не включает в себя Rectangle поэтому это НЕ ПРАВИЛЬНО!!!

/* Интерфейс холста. Позволяет рисовать отрезки прямых линий и эллипсы */
class ICanvas
{
public:
    virtual void DrawLine(CPoint from, CPoint to) = 0;
};

/* Интерфейс объектов, которые могут быть нарисованы (Draw) на холсте (canvas) */
class ICanvasDrawable
{
public:
    virtual void Draw(ICanvas& canvas) const = 0;
};

/* Интерфейс объектов, умеющих говорить (Speak). */
class ISpeakable
{
public:
    virtual void Speak() const = 0;
};

/* Прямоугольник. Может быть нарисован на холсте, а также является сериализуемым */
class Rectangle
    : public ISerializable
    , public ICanvasDrawable
{
public:
    Rectangle(CPoint leftTop, double width, double height)
            : m_leftTop(leftTop)
            , m_width(width)
            , m_height(height)
    {}
    void SaveTo(std::ostream& stream) const final
    {
        stream << m_leftTop.x << " " << m_leftTop.y << " " << m_width << " " << m_height;
    }
    void RestoreFrom(std::istream& stream) final
    {
        CPoint leftTop;
        double width;
        double height;
        if (stream >> leftTop.x && stream >> leftTop.y && stream >> width && stream >> height)
        {
            m_leftTop.x = leftTop.x;
            m_leftTop.y = leftTop.y;
            m_width = width;
            m_height = height;
        }
        else
        {
            throw std::runtime_error("Invalid state for rectangle");
        }
    }

    CPoint GetLeftTop() const
    {
        return m_leftTop;
    }

    CPoint GetRightTop() const
    {
        return CPoint({ m_leftTop.x + m_width, m_leftTop.y });
    }

    CPoint GetRightBottom() const
    {
        return CPoint({ m_leftTop.x + m_width, m_leftTop.y + m_height });
    }

    CPoint GetLeftBottom() const
    {
        return CPoint({ m_leftTop.x, m_leftTop.y + m_height });
    }

    void Draw(ICanvas& canvas) const final
    {
        canvas.DrawLine(GetLeftTop(), GetRightTop());
        canvas.DrawLine(GetRightTop(), GetRightBottom());
        canvas.DrawLine(GetRightBottom(), GetLeftBottom());
        canvas.DrawLine(GetLeftBottom(), GetLeftTop());
    }

private:
    CPoint m_leftTop;
    double m_width;
    double m_height;
};

/* Эллипс. Может быть нарисован на холсте, а также является сериализуемым */
class Ellipse /* Написать недостающий код */
{
    /* Написать недостающий код */
};

/* Треугольник. Может быть нарисован на холсте, а также является сериализуемым */
class Triangle /* Написать недостающий код */
{
    /* Написать недостающий код */
};

/* Холст. Вместо фактического рисования выводит в cout команды рисования и их параметры */
class CoutCanvas : public ICanvas
{
    void DrawLine(CPoint from, CPoint to) final
    {
        std::cout << "Draw line from " << from.x << " " << from.y << " to " << to.x << " " << to.y << std::endl;
    }
};

/* Кот. Обладает координатами (в центре головы). Может быть нарисован на холсте
 может говорить (мяукая) */
class Cat final : public ISpeakable
{
public:
    Cat() {};
    void Speak() const final
    {
        std::cout << "meow" << std::endl;
    }
};

/* Человек. Обладает именем и годом рождения.
может говорить (называет своё имя и год рождения) */
class Person : public ISpeakable
{
    void Speak() const final
    {
        std::cout << "My name is " << m_name << " and I was born at " << m_birthYear << std::endl;
    }

public:
    Person(std::string name, int birthYear)
            : m_name(name)
            , m_birthYear(birthYear)
    {}

private:
    std::string m_name;
    int m_birthYear;
};

/* Ведёт разговор с набором объектов, с которыми можно побеседовать */
void SmallTalk(std::vector<std::shared_ptr<ISpeakable>> const& speakableObjects)
{
    for (auto& object : speakableObjects)
    {
        object->Speak();
    }
}

///* Ведёт разговор с набором объектов, с которыми можно побеседовать */
//void SmallTalk(std::vector<ISpeakable> const& speakableObjects)
//{
//    for (auto& object : speakableObjects)
//    {
//        object.Speak();
//    }
//}

/* Рисует набор объектов, которые можно нарисовать на переданном холсте (принимает объекты и холст) */
void Draw(std::vector<std::shared_ptr<ICanvasDrawable>> const& drawableObjects, CoutCanvas canvas)
{
    for (auto& object : drawableObjects)
    {
        object->Draw(canvas);
    }
}

/* Копирует состояние из одного сериализуемого объекта в другой */
void CopyState(const ISerializable& from, ISerializable& to)
{
    std::stringstream stream;
    from.SaveTo(stream);
    to.RestoreFrom(stream);
}

int main()
{
    /*
    Нарисовать при помощи функции Draw домик с котиком рядом с ним:
        /\
       /  \
      / O  \
     --------
      |    |
      |    |
      ------
      до 8 баллов (8-6-4)
    */
    Rectangle houseRect(CPoint{ 30, 30 }, 30, 30);
    CoutCanvas canvas;
    std::vector<std::shared_ptr<ICanvasDrawable>> drawableObjects;
    drawableObjects.push_back(std::make_shared<Rectangle>(houseRect));
    Draw(drawableObjects, canvas);

    /* Создать прямоугольник.
     Скопировать в него при помощи CopyState состояние из прямоугольника,
     задающего стены дома
      до 6 баллов (6-5-3)
    */
    Rectangle rect(CPoint{ 0, 0 }, 10, 10);
    CopyState(houseRect, rect);
    std::cout << std::endl;
    rect.Draw(canvas);

    /*
    Создать человека по имени Ivanov Ivan 1980 года рождения.
    При помощи SmallTalk побеседовать с этим человеом и вышесозданным котом
      до 6 баллов (6-5-3)
    */
    std::cout << std::endl;
    Person person("Ivanov Ivan", 1977);
    Cat cat;
    std::vector<std::shared_ptr<ISpeakable>> speakableObjects;
    speakableObjects.push_back(std::make_shared<Person>(person));
    speakableObjects.push_back(std::make_shared<Cat>(cat));
    SmallTalk(speakableObjects);

    return 0;
}