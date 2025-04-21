#include "simple_test.h"

namespace PicoCore::Testing
{

void SimpleTest::RegisterTest(Test test)
{
    m_tests.push_back(test);
}

TestReports SimpleTest::RunTests()
{
    std::vector<TestReport> reports = std::vector<TestReport>(m_tests.size());
    
    size_t report_index = 0;
    for(auto it = m_tests.begin(); it != m_tests.end(); ++it)
    {
        const bool result = it->function();
        reports[report_index] = TestReport { .name = it->name, .result = result };
        ++report_index;
    }

    return TestReports(reports);
}

void SimpleTest::ClearTests()
{
    m_tests.clear();
}

} // namespace PicoCore::Testing