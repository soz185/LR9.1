// Работа с векторами и радиусами цилиндров.

#include <iostream>
#include <corecrt_math_defines.h>

class Radius {
private:
	double radius;
public:
	Radius()
	{
		this->radius = 0;
	}
	void initRadius(double rad)
	{
		radius = rad;
	}
	void readRadius()
	{
		std::cin >> radius;
	}
	void displayRadius()
	{
		std::cout << radius;
	}
	Radius addRadius(Radius rad1, Radius rad2)
	{
		radius = rad1.radius + rad2.radius;
		return *this;
	}
	double returnRadius()
	{
		return radius;
	}
	Radius& operator ++()
	{
		this->radius++;
		return *this;
	}
	Radius operator ++(int unused)
	{
		Radius c = *this;
		++* this;
		return c;
	}

};

class Vector {
private:
	double X;
	double Y;
	double Z;
	Radius cylinderRadius;
public:
	static int countOfVectors;

	Vector()
	{
		X = 0;
		Y = 0;
		Z = 0;
		cylinderRadius.initRadius(0);
		Vector::countOfVectors++;
	}
	Vector(double X, double y, double z, Radius rad)
	{
		this->X = X;
		this->Y = y;
		this->Z = z;
		this->cylinderRadius = rad;
		Vector::countOfVectors++;
	}

	Vector(int n)
	{
		this->X = n;
		this->Y = n;
		this->Z = n;
		this->cylinderRadius.initRadius(n);
		Vector::countOfVectors++;
	}

	Vector(const Vector& vector)
	{
		this->X = vector.X * 2;
		this->Y = vector.Y * 2;
		this->Z = vector.Z * 2;
		this->cylinderRadius = vector.cylinderRadius;
	}

	~Vector() { if (Vector::countOfVectors > 0) Vector::countOfVectors--; }

	static int getCountOfVectors()
	{
		return Vector::countOfVectors;
	}

	void read()
	{
		std::cin >> this->X >> this->Y >> this->Z;
		this->cylinderRadius.readRadius();
	}

	void display()
	{
		std::cout << this->X << "; " << this->Y << "; " << this->Z;
		std::cout << ", радиус = ";
		cylinderRadius.displayRadius();
	}

	Vector add(Vector vector)
	{
		Vector c;
		c.X = this->X + vector.X;
		c.Y = this->Y + vector.Y;
		c.Z = this->Z + vector.Z;
		c.cylinderRadius.addRadius(this->cylinderRadius, vector.cylinderRadius);
		return c;
	}

	double length()
	{
		double length = sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
		return length;
	}

	void length(double* length)
	{
		*length = sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
	}

	void length(double& length)
	{
		length = sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
	}


	double scalar(Vector vector)
	{
		double scalar = this->X * vector.X + this->Y * vector.Y + this->Z * vector.Z;
		return scalar;
	}

	friend double cylinderVolume(Vector vector);

	Vector operator+(Vector vector)
	{
		Vector c;
		c.X = this->X + vector.X;
		c.Y = this->Y + vector.Y;
		c.Z = this->Z + vector.Z;
		c.cylinderRadius.addRadius(this->cylinderRadius, vector.cylinderRadius);
		return c;
	}

	Vector& operator=(Vector &vector)
	{
		this->X = vector.X;
		this->Y = vector.Y;
		this->Z = vector.Z;
		this->cylinderRadius = vector.cylinderRadius;
		return *this;
	}

	Vector& operator ++()
	{
		this->X++;
		this->Y++;
		this->Z++;
		this->cylinderRadius++;
		return *this;
	}

	Vector operator ++(int unused)
	{
		Vector c = *this;
		++* this;
		return c;
	}
};

int Vector::countOfVectors = 0;

double cylinderVolume(Vector vector)
{
	double volume = vector.cylinderRadius.returnRadius() * vector.cylinderRadius.returnRadius() * vector.length() * M_PI;
	return volume;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	std::string str("Работа с векторами и радиусами цилиндров.\n");
	int length_str = str.length();
	std::cout << str << "Длина строки " << length_str << "\n";
	Vector a, c;
	Radius rad;
	rad.initRadius(1.5);
	Vector b(1, 0, -2, rad);
	//b.init(1, 0, -2, rad);
	printf("Количество созданных векторов: %d\n", Vector::getCountOfVectors());

	printf("Введите координаты и радиус a: ");
	a.read();

	printf("Цилиндры:\n");
	printf("a ");
	a.display();
	puts("");
	printf("b ");
	b.display();
	puts("");

	b++;
	b.display();
	puts("");

	++b;
	b.display();
	puts("");

	//c = a + b;
	//printf("Сложение цилиндров a и b:\n");
	////c = a.add(b);
	//printf("c ");
	//c.display();

	double length1 = 0;
	double length2 = 0;
	a.length(&length1);
	a.length(&length2);
	printf("\nДлина вектора a равна %g\n", a.length());
	printf("Длина вектора a равна %g (через указатель)\n", length1);
	printf("Длина вектора a равна %g (через ссылку)\n", length2);

	printf("Объем цилиндра a равен %g\n", cylinderVolume(a));
	printf("Скалярное произведение векторов a и b равно %g\n", a.scalar(b));

	Vector arr[3] = {1, 2, 3};
	printf("arr[0] ");
	arr[0].display();
	puts("");
	Vector arrCopy = arr[0];
	printf("arrCopy ");
	arrCopy.display();
	puts("");

	printf("Динамические переменные.\n");
	Vector* din_a = new Vector();
	Vector* din_b = new Vector(1, 0, -2.1, rad);
	//(*din_b).init(1, 0, -2.1, rad);
	Vector* din_c = new Vector();
	printf("Количество созданных векторов: %d\n", Vector::getCountOfVectors());

	Vector* d;
	d = (Vector*)malloc(sizeof(Vector));
	free(d);
	d = (Vector*)calloc(2, sizeof(Vector));
	d = (Vector*)realloc(d, 3 * sizeof(Vector));
	free(d);

	printf("Введите координаты и радиус a: ");
	(*din_a).read();
	printf("Цилиндры:\n");
	printf("a ");
	(*din_a).display();
	puts("");
	printf("b ");
	(*din_b).display();
	puts("");

	printf("Мелкое копирование.\n");
	din_a = din_b;
	printf("a = b =  ");
	(*din_a).display();
	puts("");
	(*din_b)++;
	printf("b + 1, a =  ");
	(*din_a).display();
	puts("");

	printf("Глубокое копирование.\n");
	*din_b = *din_c;
	printf("b = c =  ");
	(*din_b).display();
	puts("");
	(*din_c)++;
	printf("c + 1, b =  ");
	(*din_b).display();
	puts("");

	//printf("Сложение цилиндров a и b:\n");
	//(*din_c) = (*din_a).add(*din_b);
	//printf("c ");
	//(*din_c).display();

	printf("\nДлина вектора a равна %g\n", (*din_a).length());
	printf("Скалярное произведение векторов a и b равно %g\n", (*din_a).scalar(*din_b));
	delete din_a;
	delete din_b;
	delete din_c;

	printf("Динамический массив объектов.\n");
	Vector* din_mas_obj;
	din_mas_obj = new Vector[3]{1, 2, 0};
	//din_mas_obj[1].init(1, -3, 0, rad);
	printf("Количество созданных векторов: %d\n", Vector::getCountOfVectors());

	printf("Введите координаты и радиус a: ");
	din_mas_obj[0].read();
	printf("Цилиндры:\n");
	printf("a ");
	din_mas_obj[0].display();
	puts("");
	printf("b ");
	din_mas_obj[1].display();
	puts("");

	//printf("Сложение цилиндров a и b:\n");
	//din_mas_obj[2] = din_mas_obj[0].add(din_mas_obj[1]);
	//printf("c ");
	//din_mas_obj[2].display();

	printf("\nДлина вектора a равна %g\n", din_mas_obj[0].length());
	printf("Скалярное произведение векторов a и b равно %g\n", din_mas_obj[0].scalar(din_mas_obj[1]));
	delete[] din_mas_obj;
	return 0;
}
