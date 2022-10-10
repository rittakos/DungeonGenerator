#pragma once


class GenerationSettings
{
private:
	bool	fixSeed;
	long	seed;


	void	generateSeed();

public:
	GenerationSettings();

	void	setFixSeed(int seed);
	int		getSeed() const;
};