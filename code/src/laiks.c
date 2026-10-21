#include "laiks.h"

laiks_t Laiks_Seconds(float t)
{
	return (laiks_t)
	{
		(unsigned long long)(t * 1e9)
	};
}
laiks_t Laiks_Milliseconds(float t)
{
	return (laiks_t)
	{
		(unsigned long long)(t * 1e6)
	};
}

void Laiks_AddSeconds(laiks_t *l, float t)
{
	l->ns += (unsigned long long)(t * 1e9);
}
void Laiks_AddMillliseconds(laiks_t *l, float t)
{
	l->ns += (unsigned long long)(t * 1e6);
}

float Laiks_InSeconds(laiks_t l)
{
	return (float)(l.ns) / (float)(1e9);
}
float Laiks_InMilliseconds(laiks_t l)
{
	return (float)(l.ns) / (float)(1e6);
}

char CheckTimer(Taimeris_t *timer, laiks_t time)
{
	if (!timer) return false;
	if (timer->enabled && (time.ns - timer->lastTime.ns >= timer->period.ns))
	{
		timer->lastTime = time;
		if (timer->oneTime) timer->enabled = false;
		return true;
	}
	return false;
}

void InitTimer(Taimeris_t *timer, laiks_t period, char enabled, char oneTime)
{
	timer->lastTime.ns = 0;
	timer->period = period;
	timer->enabled = enabled;
	timer->oneTime = oneTime;
}

void EnableTimer(Taimeris_t *timer, laiks_t time)
{
	timer->lastTime = time;
	timer->enabled = true;
}

void DisableTimer(Taimeris_t *timer, laiks_t time)
{
	timer->lastTime = time;
	timer->enabled = false;
}
