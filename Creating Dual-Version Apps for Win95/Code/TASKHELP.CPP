#include <windows.h>
#include <toolhelp.h>

HMODULE ModuleFromTask(HTASK hTask)
{
    TASKENTRY te;
    te.dwSize = sizeof(te);
    if (TaskFindHandle(&te, hTask))
        return (te.hModule);
    return (NULL);
}

HTASK TaskFromInstance(HINSTANCE hInstance)
{
    TASKENTRY te;
    te.dwSize = sizeof(te);
    BOOL fLoop = TaskFirst(&te);
    while (fLoop)
    {
        if (te.hInst == hInstance)
            return (te.hTask);
        fLoop = TaskNext(&te);
    }
    return (NULL);
}

