/**
 * @file
 * VuoProtocol implementation.
 *
 * @copyright Copyright © 2012–2021 Kosada Incorporated.
 * This code may be modified and distributed under the terms of the GNU Lesser General Public License (LGPL) version 2 or later.
 * For more information, see https://vuo.org/license.
 */

#include "VuoProtocol.hh"

#include "VuoRunner.hh"
#include "VuoStringUtilities.hh"


static dispatch_once_t VuoProtocolsCreated = 0;	///< Make sure this process only has a single instance of each protocol.

vector<VuoProtocol *> VuoProtocol::protocols;
string VuoProtocol::imageFilter = "VuoImageFilter";			///< Processes an existing image.
string VuoProtocol::imageGenerator = "VuoImageGenerator";	///< Produces a new image.
string VuoProtocol::imageTransition = "VuoImageTransition";	///< Transitions between two images.

/**
 * Returns the available protocols.
 */
vector<VuoProtocol *> VuoProtocol::getProtocols(void)
{
	dispatch_once(&VuoProtocolsCreated, ^{
					  VuoProtocol *imageFilterProtocol = new VuoProtocol(imageFilter, "Image Filter");
					  imageFilterProtocol->addInputPort("time", "VuoReal");
					  imageFilterProtocol->addInputPort("image", "VuoImage");
					  imageFilterProtocol->addOutputPort("outputImage", "VuoImage");
					  protocols.push_back(imageFilterProtocol);

					  VuoProtocol *imageGeneratorProtocol = new VuoProtocol(imageGenerator, "Image Generator");
					  imageGeneratorProtocol->addInputPort("time", "VuoReal");
					  imageGeneratorProtocol->addInputPort("width", "VuoInteger");
					  imageGeneratorProtocol->addInputPort("height", "VuoInteger");
					  imageGeneratorProtocol->addOutputPort("outputImage", "VuoImage");
					  protocols.push_back(imageGeneratorProtocol);

					  VuoProtocol *imageTransitionProtocol = new VuoProtocol(imageTransition, "Image Transition");
					  imageTransitionProtocol->addInputPort("time", "VuoReal");
					  imageTransitionProtocol->addInputPort("progress", "VuoReal");
					  imageTransitionProtocol->addInputPort("startImage", "VuoImage");
					  imageTransitionProtocol->addInputPort("endImage", "VuoImage");
					  imageTransitionProtocol->addOutputPort("outputImage", "VuoImage");
					  protocols.push_back(imageTransitionProtocol);
				  });

	return protocols;
}

/**
 * Returns the protocol with the specified unique identifier, or NULL if none matches.
 */
VuoProtocol *VuoProtocol::getProtocol(string id)
{
	getProtocols();

	for (vector<VuoProtocol *>::iterator it = protocols.begin(); it != protocols.end(); ++it)
		if ((*it)->getId() == id)
			return *it;

	VUserLog("Error: Couldn't find protocol '%s'.", id.c_str());

	return NULL;
}

/**
 * Creates a protocol.
 *
 * @param id The protocol's unique identifier.  E.g., `VuoImageFilter`.
 * @param protocolName The name of the protocol, for display purposes.
 */
VuoProtocol::VuoProtocol(string id, string protocolName)
{
	this->id = id;
	this->name = protocolName;
}

/**
 * Returns the protocol's unique identifier.
 */
string VuoProtocol::getId(void)
{
	return id;
}

/**
 * Returns the name of the protocol.
 */
string VuoProtocol::getName(void)
{
	return name;
}

/**
 * Returns an ordered list of the published input port names associated with this
 * protocol, along with their types.
 */
vector<pair<string, string> > VuoProtocol::getInputPortNamesAndTypes(void)
{
	return inputPortNamesAndTypes;
}

/**
 * Returns an ordered list of the published output port names associated with this
 * protocol, along with their types.
 */
vector<pair<string, string> > VuoProtocol::getOutputPortNamesAndTypes(void)
{
	return outputPortNamesAndTypes;
}

/**
 * Returns a boolean indicating whether the protocol has an input port with the provided @c portName.
 */
bool VuoProtocol::hasInputPort(string portName)
{
	for (vector<pair<string, string> >::iterator i = inputPortNamesAndTypes.begin(); i != inputPortNamesAndTypes.end(); ++i)
	{
		string currentPortName = i->first;
		if (currentPortName == portName)
			return true;
	}

	return false;
}

/**
 * Returns a boolean indicating whether the protocol has an output port with the provided @c portName.
 */
bool VuoProtocol::hasOutputPort(string portName)
{
	for (vector<pair<string, string> >::iterator i = outputPortNamesAndTypes.begin(); i != outputPortNamesAndTypes.end(); ++i)
	{
		string currentPortName = i->first;
		if (currentPortName == portName)
			return true;
	}

	return false;
}

/**
 * Returns the type associated with the input port that has the provided @c portName.
 */
string VuoProtocol::getTypeForInputPort(string portName)
{
	for (vector<pair<string, string> >::iterator i = inputPortNamesAndTypes.begin(); i != inputPortNamesAndTypes.end(); ++i)
	{
		string currentPortName = i->first;
		string currentPortType = i->second;
		if (currentPortName == portName)
			return currentPortType;
	}

	VUserLog("Error: Protocol '%s' has no input port with name '%s'.", this->name.c_str(), portName.c_str());
	return NULL;
}

/**
 * Returns the type associated with the output port that has the provided @c portName.
 */
string VuoProtocol::getTypeForOutputPort(string portName)
{
	for (vector<pair<string, string> >::iterator i = outputPortNamesAndTypes.begin(); i != outputPortNamesAndTypes.end(); ++i)
	{
		string currentPortName = i->first;
		string currentPortType = i->second;
		if (currentPortName == portName)
			return currentPortType;
	}

	VUserLog("Error: Protocol '%s' has no output port with name '%s'.", this->name.c_str(), portName.c_str());
	return NULL;
}

/**
 * Returns true if this composition complies with this protocol.
 *
 * A composition complies with a given protocol if, for each port specified
 * in the protocol, the composition contains a published port with a matching
 * name and type. The composition may have additional published ports and
 * still comply with the protocol.
 */
bool VuoProtocol::isCompositionCompliant(string compositionAsString)
{
	__block int charNum = 0;
	bool (^getNextLine)(string &linenumber) = ^(string &linenumber){
			linenumber = "";
			while (true)
			{
				char c = compositionAsString[charNum++];
				if (c == '\n')
					break;
				if (c == 0)
					return false;
				linenumber += c;
			}
			return true;
		};

	// label="PublishedInputs|<image>image\r|<time>time\r"
	string (^getLabel)(string linenumber) = ^(string linenumber){
			string labelToken = "label=\"";
			string::size_type labelLocation = linenumber.find(labelToken);
			if (labelLocation == string::npos)
				return (string)"";

			labelLocation += labelToken.length();
			string label;
			while (labelLocation < linenumber.length() && linenumber[labelLocation] != '"')
				label += linenumber[labelLocation++];

			return label;
		};

	// |<image>image\r
	bool (^getNextPort)(string &label, string &portID) = ^(string &label, string &portID){
			portID = "";
			string portToken = "|<";
			string::size_type portLocation = label.find(portToken);
			if (portLocation == string::npos)
				return false;

			portLocation += portToken.length();
			while (portLocation < label.length() && label[portLocation] != '>')
				portID += label[portLocation++];

			label = label.substr(portLocation);

			return true;
		};

	// _image_type="VuoImage"
	string (^getType)(string linenumber, string portID) = ^(string linenumber, string portID){
			string typeToken = "_" + portID + "_type=\"";
			string::size_type typeLocation = linenumber.find(typeToken);
			if (typeLocation == string::npos)
				return (string)"";

			typeLocation += typeToken.length();
			string type;
			while (typeLocation < linenumber.length() && linenumber[typeLocation] != '"')
				type += linenumber[typeLocation++];

			return type;
		};


	// portID => portType
	map<string,string> publishedInputs;
	map<string,string> publishedOutputs;
	string linenumber;
	while (getNextLine(linenumber))
	{
		// PublishedInputs [type="vuo.in" label="PublishedInputs|<image>image\r|<time>time\r" _image="" _image_type="VuoImage" _time="" _time_type="VuoReal"];
		// PublishedOutputs [type="vuo.out" label="PublishedOutputs|<outputImage>outputImage\l" _outputImage_type="VuoImage"];
		bool isPublishedInputs = false;
		bool isPublishedOutputs = false;
		if (VuoStringUtilities::beginsWith(linenumber, "PublishedInputs [type=\"vuo.in\" label=\"PublishedInputs|<"))
			isPublishedInputs = true;
		else if (VuoStringUtilities::beginsWith(linenumber, "PublishedOutputs [type=\"vuo.out\" label=\"PublishedOutputs|<"))
			isPublishedOutputs = true;

		if (!isPublishedInputs && !isPublishedOutputs)
			continue;

		string label = getLabel(linenumber);
		if (label == "")
			return false;

		string portID;
		while (getNextPort(label, portID))
		{
			if (isPublishedInputs)
				publishedInputs[portID] = getType(linenumber, portID);
			else
				publishedOutputs[portID] = getType(linenumber, portID);
		}

	}

	// Check whether the composition contains all of the required input ports.
	vector<pair<string, string> > protocolInputs = getInputPortNamesAndTypes();
	for (vector<pair<string, string> >::iterator i = protocolInputs.begin(); i != protocolInputs.end(); ++i)
	{
		string protocolInputName = i->first;
		string protocolInputType = i->second;

		map<string,string>::iterator publishedInput = publishedInputs.find(protocolInputName);
		if (publishedInput == publishedInputs.end() || publishedInput->second != protocolInputType)
			return false;
	}

	// Check whether the composition contains all of the required output ports.
	vector<pair<string, string> > protocolOutputs = getOutputPortNamesAndTypes();
	for (vector<pair<string, string> >::iterator i = protocolOutputs.begin(); i != protocolOutputs.end(); ++i)
	{
		string protocolOutputName = i->first;
		string protocolOutputType = i->second;

		map<string,string>::iterator publishedOutput = publishedOutputs.find(protocolOutputName);
		if (publishedOutput == publishedOutputs.end() || publishedOutput->second != protocolOutputType)
			return false;
	}

	return true;
}

/**
 * @see isCompositionCompliant
 */
bool VuoProtocol::isCompositionCompliant(VuoRunner *runner)
{
	// Check whether the composition contains all of the required input ports.
	vector<VuoRunner::Port *> inputs = runner->getPublishedInputPorts();
	vector<pair<string, string> > protocolInputs = getInputPortNamesAndTypes();
	for (vector<pair<string, string> >::iterator i = protocolInputs.begin(); i != protocolInputs.end(); ++i)
	{
		string protocolInputName = i->first;
		string protocolInputType = i->second;

		bool found = false;
		for (vector<VuoRunner::Port *>::iterator it = inputs.begin(); it != inputs.end(); ++it)
			if ((*it)->getName() == protocolInputName
			 && (*it)->getType() == protocolInputType)
			{
				found = true;
				break;
			}
		if (!found)
			return false;
	}

	// Check whether the composition contains all of the required output ports.
	vector<VuoRunner::Port *> outputs = runner->getPublishedOutputPorts();
	vector<pair<string, string> > protocolOutputs = getOutputPortNamesAndTypes();
	for (vector<pair<string, string> >::iterator i = protocolOutputs.begin(); i != protocolOutputs.end(); ++i)
	{
		string protocolOutputName = i->first;
		string protocolOutputType = i->second;

		bool found = false;
		for (vector<VuoRunner::Port *>::iterator it = outputs.begin(); it != outputs.end(); ++it)
			if ((*it)->getName() == protocolOutputName
			 && (*it)->getType() == protocolOutputType)
			{
				found = true;
				break;
			}
		if (!found)
			return false;
	}

	return true;
}

/**
 * Returns the protocols the composition adheres to.
 */
vector<VuoProtocol *> VuoProtocol::getCompositionProtocols(string compositionAsString)
{
	vector<VuoProtocol *> allProtocols = VuoProtocol::getProtocols();
	vector<VuoProtocol *> adheresToProtocols;
	for (vector<VuoProtocol *>::iterator i = allProtocols.begin(); i != allProtocols.end(); ++i)
		if ((*i)->isCompositionCompliant(compositionAsString))
			adheresToProtocols.push_back(*i);
	return adheresToProtocols;
}

/**
 * Returns the protocols the composition adheres to.
 */
vector<VuoProtocol *> VuoProtocol::getCompositionProtocols(VuoRunner *runner)
{
	vector<VuoProtocol *> allProtocols = VuoProtocol::getProtocols();
	vector<VuoProtocol *> adheresToProtocols;
	for (vector<VuoProtocol *>::iterator i = allProtocols.begin(); i != allProtocols.end(); ++i)
		if ((*i)->isCompositionCompliant(runner))
			adheresToProtocols.push_back(*i);
	return adheresToProtocols;
}

/**
 * Adds a published input port to the protocol.
 *
 * @param portName The name of the input port.
 * @param portType The type of the input port.
 */
void VuoProtocol::addInputPort(string portName, string portType)
{
	pair<string, string> portNameAndType = make_pair(portName, portType);

	for (vector<pair<string, string> >::iterator i = inputPortNamesAndTypes.begin(); i != inputPortNamesAndTypes.end(); ++i)
	{
		string currentPortName = i->first;
		if (currentPortName == portName)
		{
			VUserLog("Error: Protocol '%s' already had an input port with name '%s'.", this->name.c_str(), portName.c_str());
			return;
		}
	}

	inputPortNamesAndTypes.push_back(portNameAndType);
}

/**
 * Adds a published output port to the protocol.
 *
 * @param portName The name of the output port.
 * @param portType The type of the output port.
 */
void VuoProtocol::addOutputPort(string portName, string portType)
{
	pair<string, string> portNameAndType = make_pair(portName, portType);

	for (vector<pair<string, string> >::iterator i = outputPortNamesAndTypes.begin(); i != outputPortNamesAndTypes.end(); ++i)
	{
		string currentPortName = i->first;
		if (currentPortName == portName)
		{
			VUserLog("Error: Protocol '%s' already had an output port with name '%s'.", this->name.c_str(), portName.c_str());
			return;
		}
	}

	outputPortNamesAndTypes.push_back(portNameAndType);
}
