#include "collision.h"
#include "raymath.h"
#include "mathUttils.h"

bool Intersects(Body* bodyA, Body* bodyB)
{
	float distance = Vector2Distance(bodyA->position,bodyB->position);
	float radius = bodyA->size + bodyB->size;

	return (distance <= radius);
}


void Collision::CreateContacts(const bodies_t& bodies, contacts_t& contacts)
{
	for (int i = 0; i < bodies.size(); i++)
	{
		Body* bodyA = bodies[i];
		for (int j = i + 1; j < bodies.size(); j++)
		{
			Body* bodyB = bodies[j];
			if (bodyB->type != Body::Type::Dynamic) continue;

			if (Intersects(bodyA, bodyB))
			{
				Contact contact;
				contact.bodyA = bodyA;
				contact.bodyB = bodyB;

				Vector2 direction = bodyA->position - bodyB->position;
				float distanceSqr = Vector2LengthSqr(direction);
				if (distanceSqr <= EPSILON)
				{
					direction = Vector2{ randomf(-0.05f, 0.05f), randomf(-0.05f, 0.05f) };
					distanceSqr = Vector2LengthSqr(direction);
				}

				float distance = sqrtf(distanceSqr);
				float radius = bodyA->size + bodyB->size;
				//The penetration depth between two circles is calculated by subtracting the distance between their centers from the sum of their radii:
				contact.depth = distance - radius;
				contact.normal = Vector2Normalize(direction); //<normalize direction, can use normalize function or direction / distance>;
				contact.restitution = (bodyA->restitution + bodyB->restitution) / 2;//<get average restitution of both bodies>;

				contacts.push_back(contact);
			}
		}
	}
}

void Collision::ResolveContacts(contacts_t& contacts)
{
	for (auto& contact : contacts)
	{
		// compute relative velocity
		Vector2 rv = contact.bodyA->velocity - contact.bodyB->velocity;
			// project relative velocity onto the contact normal
		float nv = Vector2DotProduct(rv, contact.normal);
			// skip if bodies are separating
			if (nv > 0) continue;

		// compute impulse magnitude
			float totalInverseMass = contact.bodyA->invMass + contact.bodyB->invMass;
			float impulseMagnitude = -(1 + contact.restitution) * nv / totalInverseMass;

		// compute impulse vector
			Vector2 impulse = contact.normal * impulseMagnitude;

			// apply impulses to both bodies
			contact.bodyA->ApplyForce(impulse, Body::ForceMode::Impulse);
		contact.bodyB->ApplyForce(Vector2Negate(impulse), Body::ForceMode::Impulse);
	}
}

void Collision::SeparateContacts(contacts_t& contacts)
{
	for (auto contact : contacts)

	{
		float totalInverseMass = contact.bodyA->invMass + contact.bodyB->invMass;
		if (totalInverseMass == 0) continue; 

		float penetration = -contact.depth;
		if (penetration <= 0) continue; 

		Vector2 separation = contact.normal * (penetration / totalInverseMass);
		contact.bodyA->position = contact.bodyA->position + (separation * contact.bodyA->invMass);
		contact.bodyB->position = contact.bodyB->position - (separation * contact.bodyB->invMass);
	}
}
