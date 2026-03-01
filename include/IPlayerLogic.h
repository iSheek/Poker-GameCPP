#pragma once

class IPlayerLogic
{
public:
	virtual void MakeDecision() = 0;
	virtual ~IPlayerLogic() = default;
};
