class Pngquant < Formula
  desc "PNG image optimizing utility"
  homepage "https://pngquant.org/"
  url "https://github.com/pornel/pngquant.git",
      :tag => "2.10.2",
      :revision => "f10f5d217c170d7aff4d80b88bdc563bd56babef"
  head "https://github.com/pornel/pngquant.git"

  bottle do
    sha256 high_sierra: "a7cf5dcbf8c6ab8f972e3c7f3d7a30f0f6e7d61fe71ec71cc8c4bda8202d347a"
    sha256 sierra:      "b0f4b97ed674cb11b17800d1e4ec1f313a17075710781d285efa27c37043e7a9"
    sha256 el_capitan:  "d11640da698b0bc298dbcf57e2153e9e0db0beadf8414dd4b326388b92ee909f"
    sha256 yosemite:    "dd5333cb7c02d99eee6371f542ca14255e9b5c44f2191694e7bf60d4b0f6240a"
  end

  depends_on "pkg-config" => :build
  depends_on "rust" => :build
  depends_on "libpng"
  depends_on "little-cms2"

  def install
    system "cargo", "build", "--release"
    bin.install "target/release/pngquant"
    man1.install "pngquant.1"
  end

  test do
    system "#{bin}/pngquant", test_fixtures("test.png"), "-o", "out.png"
    File.exist? testpath/"out.png"
  end
end
