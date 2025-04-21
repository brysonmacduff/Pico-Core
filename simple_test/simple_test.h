#include <functional>
#include <string>
#include <deque>
#include <iterator>
#include <vector>

namespace PicoCore::Testing
{

#define ASSERT_EQUAL [](auto left, auto right) { return left == right; }
#define ASSERT_NOT_EQUAL [](auto left, auto right) { return left != right; }
#define ASSERT_TRUE [](auto proposition) { return proposition == true; }
#define ASSERT_FALSE [](auto proposition) { return proposition == false; }

struct Test
{
    std::string name;
    std::function<bool()> function;
};

struct TestReport
{
    std::string name;
    bool result;
};

class SimpleTest;

class TestReports
{
friend SimpleTest;
public:
    ~TestReports() = default;

    auto Begin()
    { 
        return m_reports.begin();
    }
    
    auto End()
    {
        return m_reports.end();
    }

protected:
    TestReports(std::vector<TestReport> reports) : m_reports(reports){}
    std::vector<TestReport> m_reports;
};

class SimpleTest
{

public:

    ~SimpleTest() = default;
    SimpleTest() = default;

    void RegisterTest(Test test);
    TestReports RunTests();
    void ClearTests();

protected:
    std::deque<Test> m_tests;

};
} // namespace PicoCore::Testing