#include <iostream>
#include <list>
#include <string>

class IObserver
{
public:
    virtual ~IObserver() = default;
    virtual void Update(std::string const &message_from_subject) = 0;
};

class ISubject
{
public:
    virtual ~ISubject() = default;
    virtual void Attach(IObserver *observer) = 0;
    virtual void Detach(IObserver *observer) = 0;
    virtual void Notify() = 0;
};

class Subject : public ISubject
{
private:
    std::list<IObserver *> observers_;
    std::string message_;

public:
    virtual ~Subject()
    {
        std::cout << "Goodbye, I was the Subject.\n";
    }
    void Attach(IObserver *observer)
    {
        observers_.push_back(observer);
    }
    void Detach(IObserver *observer)
    {
        observers_.remove(observer);
    }
    void Notify()
    {
        for (auto observer : observers_)
        {
            observer->Update(message_);
        }
    }
    void CreateNewMessage(std::string const &new_message)
    {
        message_ = new_message;
        Notify();
    }
};

class Observer : public IObserver
{
private:
    std::string message_from_subject_;
    Subject &subject_;

public:
    Observer(Subject &subject) : subject_(subject)
    {
        subject_.Attach(this);
    }
    virtual ~Observer() = default;
    void Update(std::string const &message_from_subject)
    {
        message_from_subject_ = message_from_subject;
        std::cout << "Observer: " << message_from_subject_ << std::endl;
    }
    void UnSubscribe()
    {
        subject_.Detach(this);
    }
};

int main()
{
    Subject sub;
    Observer ob1(sub);
    Observer ob2(sub);

    sub.CreateNewMessage("Hello observer");

    ob1.UnSubscribe();
    sub.CreateNewMessage("Hello observer");
    return 0;
}