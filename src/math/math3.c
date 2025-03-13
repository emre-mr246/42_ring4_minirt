int clamp(int number, int min, int max)
{
	if (number < min)
		return (min);
	if (number > max)
		return (max);
	return (number);
}

float sq(float a)
{
	return (a * a);
}

float discriminant(float a, float b, float c)
{
	return (sq(b) - (4 * a * c));
}