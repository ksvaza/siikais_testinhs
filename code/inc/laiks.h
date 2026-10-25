#ifndef TAIMERIS_H
#define TAIMERIS_H


typedef struct {
	long long ns;
} laiks_t;

laiks_t Laiks_Seconds(float t);
laiks_t Laiks_Milliseconds(float t);

void Laiks_AddSeconds(laiks_t* l, float t);
void Laiks_AddMillliseconds(laiks_t* l, float t);

float Laiks_InSeconds(laiks_t l);
float Laiks_InMilliseconds(laiks_t l);

laiks_t Laiks_Add(laiks_t a, laiks_t b);
laiks_t Laiks_Subtract(laiks_t a, laiks_t b);

typedef struct {
	laiks_t lastTime;
	laiks_t period;
	char enabled;
	char oneTime;
}Taimeris_t;

char CheckTimer(Taimeris_t* timer, laiks_t time);
void InitTimer(Taimeris_t* timer, laiks_t period, char enabled, char oneTime);
void EnableTimer(Taimeris_t* timer, laiks_t time);
void DisableTimer(Taimeris_t* timer, laiks_t time);


#endif /* INC_TAIMERIS_H_ */
