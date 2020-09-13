using System;
using System.Drawing;
using System.Drawing.Imaging;
using Exocortex.DSP;

namespace ImageFilterApp
{
    /// <summary>
    /// Summary description for CImage.
    /// <p>Comments? Questions? Bugs? Tell Ben Houston at ben@exocortex.org</p>
    /// <p>Version: March 22, 2002</p>
    /// </summary>
    public class CImage
    {

        //--------------------------------------------------------------------------------------

        public unsafe CImage(string fileName)
        {
            Bitmap bitmap = new Bitmap(fileName);
            Size correctSize = new Size(
                (int)Math.Pow(2, Math.Ceiling(Math.Log(bitmap.Width, 2))),
                (int)Math.Pow(2, Math.Ceiling(Math.Log(bitmap.Height, 2))));
            if (correctSize != bitmap.Size)
            {
                bitmap = new Bitmap(bitmap, correctSize);
            }

            _size = correctSize;
            _data = new ComplexF[this.Width * this.Height];
            Rectangle rect = new Rectangle(0, 0, this.Width, this.Height);
            BitmapData bitmapData = bitmap.LockBits(rect, ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);
            int* colorData = (int*)bitmapData.Scan0.ToPointer();
            for (int i = 0; i < this.Width * this.Height; i++)
            {
                Color c = Color.FromArgb(colorData[i]);
                _data[i].Re = ((float)c.R + (float)c.G + (float)c.B) / (3f * 256f);
            }
            bitmap.UnlockBits(bitmapData);
        }

        //--------------------------------------------------------------------------------------

        protected ComplexF[] _data = null;
        public ComplexF[] Data
        {
            get { return _data; }
        }

        protected bool _frequencySpace = false;
        public bool FrequencySpace
        {
            get { return _frequencySpace; }
            set { _frequencySpace = value; }
        }

        protected Size _size = Size.Empty;
        public Size Size
        {
            get { return _size; }
        }
        public int Width
        {
            get { return _size.Width; }
        }
        public int Height
        {
            get { return _size.Height; }
        }

        //--------------------------------------------------------------------------------------

        public unsafe Bitmap ToBitmap()
        {
            Bitmap bitmap = new Bitmap(this.Width, this.Height, PixelFormat.Format32bppArgb);
            Rectangle rect = new Rectangle(0, 0, this.Width, this.Height);
            BitmapData bitmapData = bitmap.LockBits(rect, ImageLockMode.WriteOnly, PixelFormat.Format32bppArgb);
            int* colorData = (int*)bitmapData.Scan0.ToPointer();
            for (int i = 0; i < this.Width * this.Height; i++)
            {
                int c = Math.Min(255, Math.Max(0, (int)(256 * _data[i].GetModulus())));
                colorData[i] = Color.FromArgb(c, c, c).ToArgb();
            }
            bitmap.UnlockBits(bitmapData);
            return bitmap;
        }

        public void Save(string fileName)
        {
            this.ToBitmap().Save(fileName);
        }

        //--------------------------------------------------------------------------------------

    }
}

