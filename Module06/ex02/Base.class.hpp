#pragma once

class Base {

	public:

		virtual ~Base( void ) = 0;

		static Base *	generate(void);
		static void	identify(Base* p);
		static void	identify(Base& p);

};

class A : public Base {};
class B : public Base {};
class C : public Base {};

