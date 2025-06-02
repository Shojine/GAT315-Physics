#pragma once
#include "world.h"
class Collision
{
public:
	static void CreateContacts(const bodies_t& bodies, contacts_t& contacts);
	static void SeparateContacts(contacts_t& contacts);
};