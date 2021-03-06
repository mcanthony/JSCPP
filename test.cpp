#include "js-array.hpp"
#include "js-string.hpp"
#include "js-math.hpp"
#include "js-util.hpp"

#include <assert.h>
#include <string>
#include <iostream>

using std::cout;
using std::endl;

int main() {

	// ARRAY
	// =====

	{

		using JSCPP::Array;

		{ // Creating arrays
		  // ---------------

			Array<int> empty;
			assert(empty.isEmpty());
			assert(empty.length() == 0);
			assert(empty.size() == 0);
			assert(!empty[0]);
			assert(!empty[2]);

		}

		{ // Find stuff inside
		  // -----------------

			Array<int> arr;
			assert(arr.indexOf(12) == -1);
			assert(arr.indexOf(420) == -1);
			assert(arr.indexOf(666) == -1);
			assert(!arr.contains(12));
			assert(!arr.contains(420));
			assert(!arr.contains(666));

			arr.push(12);
			arr.push(420);
			arr.push(666);
			assert(arr.indexOf(12) == 0);
			assert(arr.indexOf(420) == 1);
			assert(arr.indexOf(666) == 2);
			assert(arr.lastIndexOf(12) == 0);
			assert(arr.lastIndexOf(420) == 1);
			assert(arr.lastIndexOf(666) == 2);

		}

		{ // Mutate the array
		  // ----------------

			Array<int> arr;
			assert(arr.isEmpty());

			arr.push(12);
			arr.push(420);
			arr.push(666);
			assert(!arr.isEmpty());
			assert(arr.length() == 3);
			assert(arr.size() == 3);
			assert(arr[0] == 12);
			assert(arr[1] == 420);
			assert(arr[2] == 666);

			assert(arr.pop() == 666);
			assert(arr.length() == 2);
			assert(arr.size() == 2);
			assert(arr[0] == 12);
			assert(arr[1] == 420);
			assert(!arr[2]);

			assert(arr.shift() == 12);
			assert(arr[0] == 420);
			assert(!arr[1]);
			assert(!arr[2]);
			assert(arr.size() == 1);

			arr.unshift(69);
			assert(arr[0] == 69);
			assert(arr[1] == 420);
			assert(arr.size() == 2);

		}

		{ // Reverse an array
			// ----------------

			Array<int> arr;

			arr.push(12);
			arr.push(420);
			arr.push(666);
			arr.push(420);
			arr.push(666);

			arr.reverse();

			assert(arr[0] == 666);
			assert(arr[1] == 420);
			assert(arr[2] == 666);
			assert(arr[3] == 420);
			assert(arr[4] == 12);

		}

		{ // Turn the array into other stuff
		  // -------------------------------

			Array<int> arr;
			assert(arr.join() == "");
			assert(arr.join(",") == "");
			assert(arr.toString() == "");

			arr.push(12);
			arr.push(420);
			arr.push(666);
			assert(arr.join() == "12,420,666");
			assert(arr.join(" - ") == "12 - 420 - 666");
			assert(arr.join("") == "12420666");
			assert(arr.toString() == "12,420,666");

			std::vector<int> vec = arr.toStdVector();
			assert(vec.size() == 3);
			assert(vec.front() == 12);

		}

	}

	// STRING
	// ======

	{

		using JSCPP::String;

		{ // Creating strings
		  // ----------------

			String empty;
			assert(empty == "");
			assert(empty.length() == 0);
			assert(empty.isEmpty());

			String name = "Ron";
			assert(name == "Ron");
			assert(name.length() == 3);
			assert(name.size() == 3);
			assert(!name.isEmpty());

			std::string stdnombre = "Ronaldo";
			String nombre = stdnombre;
			assert(nombre == "Ronaldo");

			char c = 'X';
			String letter = c;
			assert(letter == "X");
			assert(letter == 'X');

			assert(String::fromCharCode(65) == "A");

		}

		{ // Converting to std::string
		  // -------------------------

			String name = "Champ Kind";
			std::string stdname = name.toStdString();
			assert(stdname == "Champ Kind");

		}

		{ // Combining strings
		  // -----------------

			String firstName, lastName, name;
			firstName = "Brian";
			lastName = "Fantana";
			name = firstName + ' ' + lastName;

			assert(name == "Brian Fantana");
			assert(firstName + lastName == "BrianFantana");
			assert(firstName + " " + lastName == "Brian Fantana");

			name = "Brian ";
			name += "Fantana";
			assert(name == "Brian Fantana");

			name = "Brian ";
			assert(name.concat("Fantana") == "Brian Fantana");
			name = "Brian ";
			assert(name.concat(lastName) == "Brian Fantana");

		}

		{ // String access
		  // -------------

			String name = "Veronica Corningstone";
			assert(name[1] == 'e');
			assert(name[0] == 'V');
			assert(name.charAt(7) == 'a');
			assert(name.charAt(4) == 'n');
			assert(name.charCodeAt(0) == 86);
			assert(name.charCodeAt(3) == 111);

			/*
			TODO: this doesn't work
			String misspelled = "Dan Siego";
			name[0] = 'S';
			name[4] = 'D';
			assert(misspelled == "San Diego");
			*/

		}

		{ // Find things within a string
		  // ---------------------------

			String name = "Channel 4 News Team";

			assert(name.contains("Channel"));
			assert(name.contains(" "));
			assert(name.contains('4'));
			assert(!name.contains("San Diego"));

			assert(name.indexOf("Channel") == 0);
			assert(name.indexOf("4") == 8);
			assert(name.indexOf("San Diego") == -1);

			assert(name.lastIndexOf("e") == 16);
			assert(name.lastIndexOf("Channel") == 0);
			assert(name.lastIndexOf("San Diego") == -1);

			assert(name.startsWith("Channel"));
			assert(!name.startsWith("News"));
			assert(name.endsWith("Team"));
			assert(!name.endsWith("Channel"));

		}

		{ // Trimming
		  // --------

			assert(String("Hello world").trim() == "Hello world");
			assert(String("Hello world").trimLeft() == "Hello world");
			assert(String("Hello world").trimRight() == "Hello world");

			assert(String("   Hello world").trim() == "Hello world");
			assert(String("   Hello world").trimLeft() == "Hello world");
			assert(String("   Hello world").trimRight() == "   Hello world");

			assert(String("Hello world   ").trim() == "Hello world");
			assert(String("Hello world   ").trimLeft() == "Hello world   ");
			assert(String("Hello world   ").trimRight() == "Hello world");

			assert(String("   Hello world  ").trim() == "Hello world");
			assert(String("   Hello world  ").trimLeft() == "Hello world  ");
			assert(String("   Hello world  ").trimRight() == "   Hello world");

			assert(String("").trim() == "");
			assert(String("     ").trim() == "");

		}

		{ // Upper and lowercase
		  // -------------------

			String hi = "Good evening, San Diego. I'm Ron Burgundy?";
			assert(hi.toLowerCase() == "good evening, san diego. i'm ron burgundy?");
			assert(hi.toUpperCase() == "GOOD EVENING, SAN DIEGO. I'M RON BURGUNDY?");

			String empty;
			assert(empty.toLowerCase() == empty.toUpperCase());

		}

		{ // Replace
		  // -------

			String sd = "Saint Diego";
			assert(sd.replace("i", "a") == "Saant Diego");
			assert(sd.replace("Saint", "San") == "San Diego");
			assert(sd.replace("Saint Diego", "San Diago") == "San Diago");
			assert(sd.replaceAll("i", "a") == "Saant Daego");
			assert(sd.replaceAll("Saint", "San") == "San Diego");
			assert(sd.replaceAll("Saint Diego", "San Diago") == "San Diago");
			assert(sd == "Saint Diego");

		}

		{ // Slice, substr, and substring
		  // ----------------------------
		  // Examples taken from MDN:
		  // https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/slice

			String str = "The morning is upon us.";
			assert(str.slice(2, 0) == "");
			assert(str.slice(-2, 0) == "");
			assert(str.slice(2, 8) == "e morn");
			assert(str.slice(4, -2) == "morning is upon u");
			assert(str.slice(4, 3) == "");
			assert(str.slice(4, 0) == "");
			assert(str.slice(-3) == "us.");
			assert(str.slice(-3, -1) == "us");
			assert(str.slice(0, -1) == "The morning is upon us");
			assert(str == "The morning is upon us.");

		}

		{ // Using some more obscure operators
		  // ---------------------------------

			String h = "hello";
			String w = "world";

			assert(h < w);
			assert(!(h > w));
			assert(h <= w);
			assert(!(h >= w));
			assert(h <= h);
			assert(h >= h);
			assert(!(h < h));
			assert(!(h > h));

			assert((!h) == false);
			assert(!!h);

			assert((~h) == -1);

		}

	}

	// MATH
	// ====

	{

		using JSCPP::Math;

		assert(Math.E == 2.718281828459045);
		assert(Math.LN2 == 0.6931471805599453);
		assert(Math.LN10 == 2.302585092994046);
		assert(Math.LOG2E == 1.4426950408889634);
		assert(Math.LOG10E == 0.4342944819032518);
		assert(Math.PI == 3.141592653589793);
		assert(Math.SQRT1_2 == 0.7071067811865476);
		assert(Math.SQRT2 == 1.4142135623730951);

		{
			double positiveDouble = 420.69;
			double negativeDouble = -9.99;
			int positiveInt = 12;
			int negativeInt = -8;
			unsigned int uint = 19;
			assert(Math.abs(positiveDouble) == positiveDouble);
			assert(Math.abs(negativeDouble) == (-negativeDouble));
			assert(Math.abs(positiveInt) == positiveInt);
			assert(Math.abs(negativeInt) == (-negativeInt));
			assert(Math.abs(uint) == uint);
		}

		{
			assert(Math.sin(0) == 0);
			assert(Math.sin(0.0) == 0);
			assert(Math.cos(0) == 1);
			assert(Math.cos(0.0) == 1);
			assert(Math.tan(0) == 0);
			assert(Math.tan(0.0) == 0);
			assert(Math.exp(0) == 1);
			assert(Math.sqrt(0) == 0);
			assert(Math.sqrt(1) == 1);
		}

		{
			assert(Math.round(5) == 5);
			assert(Math.round(5.49) == 5);
			assert(Math.round(5.51) == 6);
			assert(Math.round(-5) == -5);
			assert(Math.round(-5.49) == -5);
			assert(Math.round(-5.51) == -6);
			assert(Math.ceil(5) == 5);
			assert(Math.ceil(5.49) == 6);
			assert(Math.ceil(5.51) == 6);
			assert(Math.ceil(-5) == -5);
			assert(Math.ceil(-5.49) == -5);
			assert(Math.ceil(-5.51) == -5);
			assert(Math.floor(5) == 5);
			assert(Math.floor(5.49) == 5);
			assert(Math.floor(5.51) == 5);
			assert(Math.floor(-5) == -5);
			assert(Math.floor(-5.49) == -6);
			assert(Math.floor(-5.51) == -6);
		}

		{
			assert(Math.max(0, 0) == 0);
			assert(Math.max(0, 1) == 1);
			assert(Math.max(1, 0) == 1);
			assert(Math.max(1, 1) == 1);
			assert(Math.max(1, 2) == 2);
			assert(Math.max(-1, 2) == 2);
			assert(Math.max(1, -2) == 1);
			assert(Math.max(2.1, 0) == 2.1);
			assert(Math.max(0, 2.1) == 2.1);
			assert(Math.max(1.9, 1.9) == 1.9);
			assert(Math.max(1.2, 4.20) == 4.2);
			assert(Math.max(-1.2, 4.20) == 4.2);
			assert(Math.max(1.2, -4.20) == 1.2);
		}

		{
			assert(Math.min(0, 0) == 0);
			assert(Math.min(0, 1) == 0);
			assert(Math.min(1, 0) == 0);
			assert(Math.min(1, 1) == 1);
			assert(Math.min(1, 2) == 1);
			assert(Math.min(-1, 2) == -1);
			assert(Math.min(1, -2) == -2);
			assert(Math.min(2.1, 0) == 0);
			assert(Math.min(0, 2.1) == 0);
			assert(Math.min(1.9, 1.9) == 1.9);
			assert(Math.min(1.2, 4.20) == 1.2);
			assert(Math.min(-1.2, 4.20) == -1.2);
			assert(Math.min(1.2, -4.20) == -4.2);
		}

		{
			double rand;
			for (int i = 0; i < 1000; i ++) {
				rand = Math.random();
				assert(rand >= 0);
				assert(rand < 1);
			}
		}

		{
			assert(Math.sign(0) == 0);
			assert(Math.sign(0.0) == 0);
			assert(Math.sign(1.0) == 1);
			assert(Math.sign(2.0) == 1);
			assert(Math.sign(6.9) == 1);
			assert(Math.sign(-1.0) == -1);
			assert(Math.sign(-2.0) == -1);
			assert(Math.sign(-6.9) == -1);
		}

	}

	// UTILITIES
	// =========

	{

		{ // parseInt
		  // --------

			using JSCPP::parseInt;

			assert(parseInt("420") == 420);
			assert(parseInt("3.14159") == 3);
			assert(parseInt("8 is a cool number") == 8);
			assert(parseInt("But 12 is cooler") == 0);
			assert(parseInt("But 12 is cooler") == 0);

		}

	}

}
