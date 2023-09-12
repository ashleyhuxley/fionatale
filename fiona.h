#ifndef FIONA_H
#define FIONA_H

class Fiona
{
	public:
		Fiona();
		void drawMain();
		bool hit(int hpHit);
		bool canSpare;
		void scremOut();
		void slash();
		void spare();

	private:
		int hp;
		void die();
		
};

#endif