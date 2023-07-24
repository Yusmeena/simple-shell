#include "shell.h"

/**
* exitShell - this exit the shell
* @data: Structure entail important paramenters for function
* Return: Exits the shell with a specific exit value(0)
* if data.argv[0] is not "exit"
*/
int exitShell(info_t *data)
{
	int leaveConfirm;

	if (data->argv[1]) /* Be sure argv[1] exits */
	{
		leaveConfirm = errAtoi(data->argv[1]); /* argv[1] -> intger conversion */
		if (leaveConfirm == -1) /*Analyze any failed conversions */
		{
			data->worth = 2; /* data value set to 2 */
			display_err(data, "Wrong number: ");
			eputin(data->argv[1]); /* display argv[1] */
			eputword('\n'); /* Enable a new line in a text */
			return (1);
		} /*Put argv[1] in digit_err afte converted to integer */
		data->digit_err = errAtoi(data->argv[1]);
		return (-2);
	}
	data->digit_err = -1; /*Place -1 in digit_err */
	return (-2);
}
/**
* Dirchange - modifies the present folder of the process
* @data: Structure contain important parameters for the function
* Return: Always 0
*/
int Dirchange(info_t *data)
{
	char *s, *dir, fender[1024];
	int fgdir_look;

	s = getcwd(fender, 1024); /*Take current working folder,save to s*/
	if (!s)
		putin("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1]) /* Confirm if argv[1] is given */
	{
		dir = findEnv(data, "HOME="); 
	/* Find Value of environment variable HOME */
		if (!dir)
			fgdir_look = /* TODO: what should this be? */				chdir((dir - findEnv(data, "PWD=")) ? dir :"/");
		else
			fgdir_look = chdir(dir);
	}
	else if (_strcmps(data->argv[1], "-") == 0) 
/*check if argv[1] is "-" */
	{
		if (!findEnv(data, "OLDPWD="))
		{
			putin(s); /* The working folder is displayed right now */
			_putchar('\n');
			return (1);
		}
		putin(findEnv(data, "OLDPWD=")), _putchar('\n');
		fgdir_look = /* TODO: what should this be? */
			chdir((dir = findEnv(data, "OLDPWD=")) ? : "/");
	}
	else
		fgdir_look = chdir(data-> argv[1]);
	if (fgdir_look == -1)
	{
		display_err(data, "can't cd to ");
		eputin(data->argv[1]), eputword('\n');
	}
	else
	{
		fixEnv(data, "OLDPWD", findEnv(data, "PWD="));
		fixEnv(data, "PWD", getcwd(fender, 1024));
	}
	return (0);
}
/**
* displayHelp - this give assistance and information
* @data: Structure contain important parameters for the functios
* Return: Always 0
*/

int displayHelp(info_t *data)
{
	char **arg_argv; /* Arg_array would receive the argv pointer */
	putin("help call work. Function not yet executed \n");
	if (0)
		putin(*arg_array); /* tem att_unused workaround */
	return (0);
}
