/*
	Copyright 2006-2025 The QElectroTech Team
	This file is part of QElectroTech.
	
	QElectroTech is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.
	
	QElectroTech is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with QElectroTech.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "numerotationcontextcommands.h"

#include "../diagram.h"

/**
	@brief Constructor
*/
NumerotationContextCommands::NumerotationContextCommands(const NumerotationContext &nc, Diagram *d):
	diagram_ (d),
	context_ (nc),
	strategy_ (nullptr)
{}

/**
	@brief Destructor
*/
NumerotationContextCommands::~NumerotationContextCommands()
{
	if (strategy_) delete strategy_;
}

/**
	@brief NumerotationContextCommands::next
	@return the next numerotation context
*/
NumerotationContext NumerotationContextCommands::next()
{
	NumerotationContext contextnum;

	for (int i=0; i<context_.size(); ++i) {
		QStringList str = context_.itemAt(i);
		setNumStrategy(str.at(0));
		contextnum << strategy_ -> next(context_, i);
	}
	return contextnum;
}

/**
	@brief NumerotationContextCommands::previous
	@return the previous numerotation context
*/
NumerotationContext NumerotationContextCommands::previous()
{
	NumerotationContext contextnum;

	for (int i=0; i<context_.size(); ++i) {
		QStringList str = context_.itemAt(i);
		setNumStrategy(str.at(0));
		contextnum << strategy_ -> previous(context_, i);
	}
	return contextnum;
}

/**
	@brief NumerotationContextCommands::toFinalString
	@return the string represented by the numerotation context
*/
QString NumerotationContextCommands::toRepresentedString()
{
	QString num;
	if (context_.size()) {
		for (int i=0; i<context_.size(); i++) {
			QStringList  str = context_.itemAt(i);
			setNumStrategy(str.at(0));
			num += strategy_ -> toRepresentedString(str.at(1));
		}
		return num;
	}
	if (diagram_) return (diagram_ -> defaultConductorProperties.text);
	return QString();
}

/**
	@brief NumerotationContextCommands::setNumStrategy
	apply the good strategy relative to str
*/
void NumerotationContextCommands::setNumStrategy(const QString &str) {
	if (strategy_) delete strategy_;
	if (str == "unit") {
		strategy_ = new UnitNum(diagram_);
		return;
	}
	else if (str == "unitfolio") {
		strategy_ = new UnitFNum (diagram_);
		return;
	}
	else if (str == "ten") {
		strategy_ = new TenNum (diagram_);
		return;
	}
	else if (str == "tenfolio") {
		strategy_ = new TenFNum (diagram_);
		return;
	}
	else if (str == "hundred") {
		strategy_ = new HundredNum (diagram_);
		return;
	}
	else if (str == "hundredfolio") {
		strategy_ = new HundredFNum (diagram_);
		return;
	}
	else if (str == "string") {
		strategy_ = new StringNum (diagram_);
		return;
	}
	else if (str == "idfolio") {
		strategy_ = new IdFolioNum (diagram_);
		return;
	}
	else if (str=="folio"){
		strategy_ = new FolioNum (diagram_);
		return;
	}
	else if (str=="plant"){
		strategy_ = new PlantNum (diagram_);
		return;
	}
	else if (str=="locmach"){
		strategy_ = new LocmachNum (diagram_);
		return;
	}
	else if (str=="elementline"){
		strategy_ = new ElementLineNum (diagram_);
		return;
	}
	else if (str=="elementcolumn"){
		strategy_ = new ElementColumnNum (diagram_);
		return;
	}
	else if (str=="elementprefix"){
		strategy_ = new ElementPrefixNum (diagram_);
		return;
	}
}



/**
	Constructor
*/
NumStrategy::NumStrategy (Diagram *d):
	diagram_ (d)
{}

NumStrategy::~NumStrategy()
{}

/**
	@brief NumStrategy::nextString
	@return the next value of nc at position i
*/
NumerotationContext NumStrategy::nextString (const NumerotationContext &nc,
					     const int i) const
{
	QStringList strl = nc.itemAt(i);
	NumerotationContext newnc;
	newnc.addValue(strl.at(0), strl.at(1), strl.at(2).toInt());
	return (newnc);
}

/**
	@brief NumStrategy::nextNumber
	@return the next value of nc at position i
*/
NumerotationContext NumStrategy::nextNumber (const NumerotationContext &nc,
					     const int i) const
{
	QStringList strl = nc.itemAt(i);
	NumerotationContext newnc;
	QString value = QString::number( (strl.at(1).toInt()) + (strl.at(2).toInt()) );
	newnc.addValue(strl.at(0), value, strl.at(2).toInt(), strl.at(3).toInt());
	return (newnc);
}

/**
	@brief NumStrategy::previousNumber
	@return  the previous value of nc at position i
*/
NumerotationContext NumStrategy::previousNumber(const NumerotationContext &nc,
						const int i) const
{
	QStringList strl = nc.itemAt(i);
	NumerotationContext newnc;
	QString value = QString::number( (strl.at(1).toInt()) - (strl.at(2).toInt()) );
	newnc.addValue(strl.at(0), value, strl.at(2).toInt(), strl.at(3).toInt());
	return (newnc);
}

/**
	Constructor
*/
UnitNum::UnitNum(Diagram *d):
	NumStrategy(d)
{}

/**
	@brief UnitNum::toRepresentedString
	@return the represented string of num
*/
QString UnitNum::toRepresentedString(const QString num) const
{
	return (num);
}

/**
	@brief UnitNum::next
	@return the next NumerotationContext nc at position i
*/
NumerotationContext UnitNum::next (const NumerotationContext &nc, const int i) const
{
	return (nextNumber(nc, i));
}

/**
	@brief UnitNum::previous
	@return the previous NumerotationContext nc at posiiton i
*/
NumerotationContext UnitNum::previous(const NumerotationContext &nc, const int i) const
{
	return (previousNumber(nc, i));
}

/**
	Constructor
*/
UnitFNum::UnitFNum(Diagram *d):
	NumStrategy(d)
{}

/**
	@brief UnitFNum::toRepresentedString
	@return the represented string of num
*/
QString UnitFNum::toRepresentedString(const QString num) const
{
	return (num);
}

/**
	@brief UnitFNum::next
	@return the next NumerotationContext nc at position i
*/
NumerotationContext UnitFNum::next (const NumerotationContext &nc, const int i) const
{
	return (nextNumber(nc, i));
}

/**
	@brief UnitFNum::previous
	@return the previous NumerotationContext nc at posiiton i
*/
NumerotationContext UnitFNum::previous(const NumerotationContext &nc, const int i) const
{
	return (previousNumber(nc, i));
}

/**
	Constructor
*/
TenNum::TenNum (Diagram *d):
	NumStrategy (d)
{}

/**
	@brief TenNum::toRepresentedString
	@return the represented string of num
*/
QString TenNum::toRepresentedString(const QString num) const
{
	int numint = num.toInt();
	QString numstr = num;
	if (numint<10) numstr.prepend("0");
	return (numstr);
}

/**
	@brief TenNum::next
	@return the next NumerotationContext nc at position i
*/
NumerotationContext TenNum::next (const NumerotationContext &nc, const int i) const
{
	return (nextNumber(nc, i));
}

/**
	@brief TenNum::previous
	@return the previous NumerotationContext nc at posiiton i
*/
NumerotationContext TenNum::previous(const NumerotationContext &nc, const int i) const
{
	return (previousNumber(nc, i));
}

/**
	Constructor
*/
TenFNum::TenFNum (Diagram *d):
	NumStrategy (d)
{}

/**
	@brief TenFNum::toRepresentedString
	@return the represented string of num
*/
QString TenFNum::toRepresentedString(const QString num) const
{
	int numint = num.toInt();
	QString numstr = num;
	if (numint<10) numstr.prepend("0");
	return (numstr);
}

/**
	@brief TenFNum::next
	@return the next NumerotationContext nc at position i
*/
NumerotationContext TenFNum::next (const NumerotationContext &nc, const int i) const
{
	return (nextNumber(nc, i));
}

/**
	@brief TenFNum::previous
	@return the previous NumerotationContext nc at posiiton i
*/
NumerotationContext TenFNum::previous(const NumerotationContext &nc, const int i) const
{
	return (previousNumber(nc, i));
}


/**
	Constructor
*/
HundredNum::HundredNum (Diagram *d):
	NumStrategy (d)
{}

/**
	@brief HundredNum::toRepresentedString
	@return the represented string of num
*/
QString HundredNum::toRepresentedString(const QString num) const
{
	int numint = num.toInt();
	QString numstr = num;
	if (numint<100) {
		if (numint<10) {
			numstr.prepend("00");
		}
		else numstr.prepend("0");
	}
	return (numstr);
}

/**
	@brief HundredNum::next
	@return the next NumerotationContext nc at position i
*/
NumerotationContext HundredNum::next (const NumerotationContext &nc, const int i) const
{
	return (nextNumber(nc, i));
}

/**
	@brief HundredNum::previous
	@return the previous NumerotationContext nc at posiiton i
*/
NumerotationContext HundredNum::previous(const NumerotationContext &nc, const int i) const
{
	return (previousNumber(nc, i));
}

/**
	Constructor
*/
HundredFNum::HundredFNum (Diagram *d):
	NumStrategy (d)
{}

/**
	@brief HundredFNum::toRepresentedString
	@return the represented string of num
*/
QString HundredFNum::toRepresentedString(const QString num) const
{
	int numint = num.toInt();
	QString numstr = num;
	if (numint<100) {
		if (numint<10) {
			numstr.prepend("00");
		}
		else numstr.prepend("0");
	}
	return (numstr);
}

/**
	@brief HundredFNum::next
	@return the next NumerotationContext nc at position i
*/
NumerotationContext HundredFNum::next (const NumerotationContext &nc, const int i) const
{
	return (nextNumber(nc, i));
}

/**
	@brief HundredFNum::previous
	@return the previous NumerotationContext nc at posiiton i
*/
NumerotationContext HundredFNum::previous(const NumerotationContext &nc, const int i) const
{
	return (previousNumber(nc, i));
}

/**
	Constructor
*/
StringNum::StringNum (Diagram *d):
	NumStrategy (d)
{}

/**
	@brief StringNum::toRepresentedString
	@return the represented string of num
*/
QString StringNum::toRepresentedString(const QString str) const
{
	return (str);
}

/**
	@brief StringNum::next
	@return the next NumerotationContext nc at position i
*/
NumerotationContext StringNum::next (const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}

/**
	@brief StringNum::previous
	@return the previous NumerotationContext nc at posiiton i
*/
NumerotationContext StringNum::previous(const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}

/**
	Constructor
*/
IdFolioNum::IdFolioNum (Diagram *d):
	NumStrategy (d)
{}

/**
	@brief IdFolioNum::toRepresentedString
	@return the represented string of num
*/
QString IdFolioNum::toRepresentedString(const QString str) const
{
	Q_UNUSED(str);
	return ("%id");
}

/**
	@brief IdFolioNum::next
	@return the next NumerotationContext nc at position i
*/
NumerotationContext IdFolioNum::next (const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}

/**
	@brief IdFolioNum::previous
	@return the previous NumerotationContext nc at posiiton i
*/
NumerotationContext IdFolioNum::previous(const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}

/**
	Constructor
*/
FolioNum::FolioNum (Diagram *d):
	NumStrategy (d)
{}

/**
	@brief FolioNum::toRepresentedString
	@return the represented string of folio
*/
QString FolioNum::toRepresentedString(const QString str) const
{
	Q_UNUSED(str);
	return ("%F");
}

/**
	@brief FolioNum::next
	@return the next NumerotationContext nc at position i
*/
NumerotationContext FolioNum::next (const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}

/**
	@brief FolioNum::previous
	@return the previous NumerotationContext nc at posiiton i
*/
NumerotationContext FolioNum::previous(const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}

/**
	Constructor
*/
PlantNum::PlantNum (Diagram *d):
	NumStrategy (d)
{}

/**
	@brief PlantNum::toRepresentedString
	@return the represented string of folio
*/
QString PlantNum::toRepresentedString(const QString str) const
{
	Q_UNUSED(str);
	return "%M";
}

/**
	@brief PlantNum::next
	@return the next NumerotationContext nc at position i
*/
NumerotationContext PlantNum::next (const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}

/**
	@brief PlantNum::previous
	@return the previous NumerotationContext nc at posiiton i
*/
NumerotationContext PlantNum::previous(const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}


/**
	Constructor
*/
LocmachNum::LocmachNum (Diagram *d):
	NumStrategy (d)
{}

/**
	@brief LocmachNum::toRepresentedString
	@return the represented string of folio
*/
QString LocmachNum::toRepresentedString(const QString str) const
{
	Q_UNUSED(str);
	return "%LM";
}

/**
	@brief LocmachNum::next
	@return the next NumerotationContext nc at position i
*/
NumerotationContext LocmachNum::next (const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}

/**
	@brief LocmachNum::previous
	@return the previous NumerotationContext nc at posiiton i
*/
NumerotationContext LocmachNum::previous(const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}


/**
	Constructor
*/
ElementLineNum::ElementLineNum (Diagram *d):
	NumStrategy (d)
{}

/**
	@brief ElementLineNum::toRepresentedString
	@return the represented string of folio
*/
QString ElementLineNum::toRepresentedString(const QString str) const
{
	Q_UNUSED(str);
	return "%l";
}

/**
	@brief ElementLineNum::next
	@return the next NumerotationContext nc at position i
*/
NumerotationContext ElementLineNum::next (const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}

/**
	@brief ElementLineNum::previous
	@return the previous NumerotationContext nc at posiiton i
*/
NumerotationContext ElementLineNum::previous(const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}

/**
	Constructor
*/
ElementColumnNum::ElementColumnNum (Diagram *d):
	NumStrategy (d)
{}

/**
	@brief ElementColumnNum::toRepresentedString
	@return the represented string of folio
*/
QString ElementColumnNum::toRepresentedString(const QString str) const
{
	Q_UNUSED(str);
	return "%c";
}

/**
	@brief ElementColumnNum::next
	@return the next NumerotationContext nc at position i
*/
NumerotationContext ElementColumnNum::next (const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}

/**
	@brief ElementColumnNum::previous
	@return the previous NumerotationContext nc at posiiton i
*/
NumerotationContext ElementColumnNum::previous(const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}

/**
	Constructor
*/
ElementPrefixNum::ElementPrefixNum (Diagram *d):
	NumStrategy (d)
{}

/**
	@brief ElementPrefixNum::toRepresentedString
	@return the represented string of folio
*/
QString ElementPrefixNum::toRepresentedString(const QString str) const
{
	Q_UNUSED(str);
	return "%prefix";
}

/**
	@brief ElementPrefixNum::next
	@return the next NumerotationContext nc at position i
*/
NumerotationContext ElementPrefixNum::next (const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}

/**
	@brief ElementPrefixNum::previous
	@return the previous NumerotationContext nc at posiiton i
*/
NumerotationContext ElementPrefixNum::previous(const NumerotationContext &nc, const int i) const
{
	return (nextString(nc, i));
}

