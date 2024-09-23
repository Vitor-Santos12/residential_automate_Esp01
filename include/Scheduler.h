#ifndef SCHEDULER_H
#define SCHEDULER_H

class Scheduler {
public:
    static void init();
    static void update();
    static void scheduleTask(int pin, unsigned long startTime, unsigned long duration);
};

#endif // SCHEDULER_H
