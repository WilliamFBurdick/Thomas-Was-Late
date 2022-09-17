#include "Bob.h"
#include "TextureHolder.h"

Bob::Bob()
{
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/bob.png"));
	m_JumpDuration = .25;
}

bool Bob::handleInput()
{
	m_JustJumped = false;
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		//jump only if not jumping or falling
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
	m_LeftPressed = Keyboard::isKeyPressed(Keyboard::Left);
	m_RightPressed = Keyboard::isKeyPressed(Keyboard::Right);

	return m_JustJumped;
}