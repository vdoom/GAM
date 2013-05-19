#include "PingvBot.h"

PingvBot::PingvBot(void)
{

}

PingvBot::~PingvBot(void)
{
	delete m_mesh;
}

void PingvBot::Draw()
{
	//m_mesh->RecalcMatrixGlobalOnly();
	m_mesh->Draw();
}

GAMObject* PingvBot::Clone()
{
	// Todo: Need refine
	return dynamic_cast<GAMObject*>(this);
}
