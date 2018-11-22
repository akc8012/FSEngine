#pragma once
#include "ComponentType.h"
#include "FSDebug.h"
#include "FSException.h"
#include "INameable.h"
#include "ISerializable.h"

#include <string>
#include <memory>
using std::string;
using std::to_string;
using std::unique_ptr;
using std::make_unique;

class Component : public INameable, public ISerializable
{
private:
	string name;
	bool serializable = true;

public:
	virtual ~Component();

	static const Types::ComponentType ComponentTypeId = Types::Component;
	virtual Types::ComponentType GetComponentTypeId() const;

	const string& GetName() const override;
	void SetName(const string& name) override;

	virtual json GetJson() const override;
	virtual void SetFromJson(const json& j) override;

	void SetSerializable(bool serializable) override;
	bool GetSerializable() const override;
};
