using System.Diagnostics;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Test;
using System.Numerics;
public class Test
{

    [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
    public static void TestMain()
    {
        Console.WriteLine("start");
        Stopwatch sw = Stopwatch.StartNew();
        sw.Start();

        //Vector3 v = new Vector3(1, 1, 1);
        for(int i = 0; i < 100000000; i++)
        {
            //var q = Quaternion.CreateFromYawPitchRoll(0, 0,(float) ((Math.PI / 180) * (i % 360)));
            //var t = Matrix4x4.CreateTranslation(new Vector3(0, i, 0));

            //var m = Matrix4x4.CreateFromQuaternion(q) * t;

            //Vector3.Transform(v, m);
        }

        Console.WriteLine(sw.Elapsed);
    }



}