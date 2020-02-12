void setup();
void loop();

__attribute((weak))
void main()
{
    setup();
    while(1) loop();
}
