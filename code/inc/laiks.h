#ifndef TAIMERIS_H
#define TAIMERIS_H


typedef struct {
	unsigned long long ns;
} laiks_t;

laiks_t Laiks_Seconds(float t);
laiks_t Laiks_Milliseconds(float t);

void Laiks_AddSeconds(laiks_t* l, float t);
void Laiks_AddMillliseconds(laiks_t* l, float t);

float Laiks_InSeconds(laiks_t l);
float Laiks_InMilliseconds(laiks_t l);

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
