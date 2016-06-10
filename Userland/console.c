extern void _write(char * buffer, unsigned long int);

int main(void)
{
	_write("PRUEBA DE SYSTEMCALLS\n", 22);
	return 0;
}