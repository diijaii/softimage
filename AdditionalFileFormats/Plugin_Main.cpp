#include <xsi_pluginregistrar.h>
#include <xsi_status.h>
#include <xsi_decl.h>
#include <xsi_menu.h>
#include <xsi_argument.h>

#include <stdio.h>

#include "obj.h"
#include "stl.h"
#include "ply.h"

#include "FileBrowser.h"

using namespace XSI;

XSIPLUGINCALLBACK CStatus XSILoadPlugin(PluginRegistrar& in_reg)
{
	in_reg.PutAuthor(L"Claus");
	in_reg.PutName(L"Additional File Formats Plug-in");
	in_reg.PutVersion(1, 0);
	
	in_reg.RegisterCommand(L"ImportPLY");
	in_reg.RegisterCommand(L"ImportSTL");
	in_reg.RegisterCommand(L"ExportSTL");
	in_reg.RegisterCommand(L"ImportOBJ");
	in_reg.RegisterCommand(L"ExportOBJ");

	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus XSIUnloadPlugin(const PluginRegistrar& in_reg)
{
	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus ImportSTL_Init(CRef& in_ctxt)
{
	Context ctxt(in_ctxt);

	Command cmd = ctxt.GetSource();

	ArgumentArray args = cmd.GetArguments();
	args.Add(L"FileName");

	cmd.PutDescription(L"ImportSTL([str]FolderAndFilename)");

	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus ImportSTL_Execute(XSI::CRef& in_ctxt)
{
	Application app;
	Context ctxt(in_ctxt);
	Command cmd = ctxt.GetSource();
	ArgumentArray args = cmd.GetArguments();
	CString strFolderAndFileName(args.GetItem(0).GetValue());

	if (strFolderAndFileName.IsEmpty()) {
		app.LogMessage(L"No Filename Specified in Arguments");
		return CStatus::Unexpected;
	}

	CSTL stl;
	return stl.Execute_Import(strFolderAndFileName.GetAsciiString());
}

XSIPLUGINCALLBACK CStatus ExportSTL_Init(CRef& in_ctxt)
{
	Context ctxt(in_ctxt);

	Command cmd = ctxt.GetSource();

	ArgumentArray args = cmd.GetArguments();
	args.AddWithHandler(L"Objects", siArgHandlerCollection, L"");
	args.Add(L"FolderAndFileName", L"");
	args.Add(L"ExportBinaryFormat", true);
	args.Add(L"UseLocalCoords", false);

	cmd.PutDescription(L"ExportOBJ([col]Objects, [str]FolderAndFileName, [bool]ExportBinaryFormat, [bool]UseLocalCoords)");

	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus ExportSTL_Execute(XSI::CRef& in_ctxt)
{
	Application app;
	Context ctxt(in_ctxt);
	Command cmd = ctxt.GetSource();
	ArgumentArray args = cmd.GetArguments();
	CRefArray Objects = (CRefArray)args.GetItem(0).GetValue();
	CString FolderAndFileName(args.GetItem(1).GetValue());
	bool ExportBinaryFormat(args.GetItem(2).GetValue());
	bool UseLocalCoords(args.GetItem(3).GetValue());

	if (FolderAndFileName.IsEmpty()) {
		app.LogMessage(L"No Filename Specified in Arguments");
		return CStatus::Unexpected;
	}

	CSTL stl;
	return stl.Execute_Export(Objects, FolderAndFileName.GetAsciiString(), ExportBinaryFormat, UseLocalCoords);
}

XSIPLUGINCALLBACK CStatus ExportOBJ_Init(CRef& in_ctxt)
{
	Context ctxt(in_ctxt);

	Command cmd = ctxt.GetSource();

	ArgumentArray args = cmd.GetArguments();
	args.AddWithHandler(L"Objects", siArgHandlerCollection, L"");
	args.Add(L"FolderAndFileName", L"");	
	args.Add(L"ExportColorAtVertices", true);
	args.Add(L"ExportToSeparateFiles", false);
	args.Add(L"UseLocalCoords", false);

	cmd.PutDescription(L"ExportOBJ([col]Objects, [str]FolderAndFileName, [bool]ExportColorAtVertices, [bool]ExportToSeparateFiles, [bool]UseLocalCoords)");

	return CStatus::OK;
}

XSIPLUGINCALLBACK CStatus ExportOBJ_Execute(XSI::CRef& in_ctxt)
{
	Application app;
	Context ctxt(in_ctxt);
	Command cmd = ctxt.GetSource();
	ArgumentArray args = cmd.GetArguments();
	CRefArray Objects = (CRefArray)args.GetItem(0).GetValue();
	CString FolderAndFileName(args.GetItem(1).GetValue());
	bool ExportColorAtVertices(args.GetItem(2).GetValue());
	bool ExportToSeparateFiles(args.GetItem(3).GetValue());
	bool UseLocalCoords(args.GetItem(4).GetValue());
	
	if (FolderAndFileName.IsEmpty()) {
		app.LogMessage(L"No Filename Specified in Arguments");
		return CStatus::Unexpected;
	}
	
	COBJ obj;
	return obj.Execute_Export(Objects, FolderAndFileName.GetAsciiString(), ExportColorAtVertices, ExportToSeparateFiles, UseLocalCoords);
}

XSIPLUGINCALLBACK CStatus ImportOBJ_Init(CRef& in_ctxt)
{
	Context ctxt(in_ctxt);

	Command cmd = ctxt.GetSource();

	ArgumentArray args = cmd.GetArguments();
	args.Add(L"FileName");

	cmd.PutDescription(L"ImportOBJ([str]FolderAndFilename)");

	return CStatus::OK;
}


XSIPLUGINCALLBACK CStatus ImportOBJ_Execute(XSI::CRef& in_ctxt)
{
	Application app;
	Context ctxt(in_ctxt);
	Command cmd = ctxt.GetSource();
	ArgumentArray args = cmd.GetArguments();
	CString strFolderAndFileName(args.GetItem(0).GetValue());

	if (strFolderAndFileName.IsEmpty()) {
		app.LogMessage(L"No Filename Specified in Arguments");
		return CStatus::Unexpected;
	}

	COBJ obj;
	return obj.Execute_Import(strFolderAndFileName.GetAsciiString(), true, true, true, true);
}

XSIPLUGINCALLBACK CStatus ImportPLY_Init(CRef& in_ctxt)
{
	Context ctxt(in_ctxt);

	Command cmd = ctxt.GetSource();

	ArgumentArray args = cmd.GetArguments();
	args.Add(L"FileName");

	cmd.PutDescription(L"ImportPLY([str]FolderAndFilename)");

	return CStatus::OK;
}


XSIPLUGINCALLBACK CStatus ImportPLY_Execute(XSI::CRef& in_ctxt)
{
	Application app;
	Context ctxt(in_ctxt);
	Command cmd = ctxt.GetSource();
	ArgumentArray args = cmd.GetArguments();
	CString strFolderAndFileName(args.GetItem(0).GetValue());

	if (strFolderAndFileName.IsEmpty()) {
		app.LogMessage(L"No Filename Specified in Arguments");
		return CStatus::Unexpected;
	}

	CPLY ply;
	return ply.Execute_Import(strFolderAndFileName.GetAsciiString(), true, true, true, true);
}
