#include "Thomas.h"
#include "TextureHolder.h"

Thomas::Thomas()
{
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/thomas.png"));
	m_JumpDuration = .45;
}

bool Thomas::handleInput()
{
	m_JustJumped = false;
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		//start a jump if not jumping, but only if not falling
		if (!m_IsJumping && !m_IsFalling)
		{
			m_IsJumping = true;
			m_TimeThisJump = 0;
			m_JustJumped = true;
		}
	}
	else
	{
		m_IsJumping = false;
		m_IsFalling = true;
	}
	m_LeftPressed = Keyboard::isKeyPressed(Keyboard::A);
	m_RightPressed = Keyboard::isKeyPressed(Keyboard::D);
	
	return m_JustJumped;
}