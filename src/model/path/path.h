
typedef struct step step;
typedef struct path path;

struct step {
    int index;
    int spent_time;
};

struct path {
    step *steps;
};