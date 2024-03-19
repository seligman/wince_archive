@names = ('PipeLeftBottom',
          'PipeLeftTop',
          'PipeRightBottom',
          'PipeRightTop',
          'PipeCross',
          'PipeVertical',
          'PipeHorizontal',
          'PipeBlank',
          'PipeStartUp',
          'PipeStartDown',
          'PipeStartLeft',
          'PipeStartRight',
          'PipeBlock');
# 12 - 16
# 0 - 16
# 12 - 28

$start{'PipeLeftBottom'} = ;
$start{'PipeLeftTop'} = ;
$start{'PipeRightBottom'} = ;
$start{'PipeRightTop'} = ;
$start{'PipeCross'} = ;
$start{'PipeVertical'} = ;
$start{'PipeHorizontal'} = ;
$start{'PipeBlank'} = ;
$start{'PipeStartUp'} = ;
$start{'PipeStartDown'} = ;
$start{'PipeStartLeft'} = ;
$start{'PipeStartRight'} = ;
$start{'PipeBlock'} = ;

$end{'PipeLeftBottom'} = ;
$end{'PipeLeftTop'} = ;
$end{'PipeRightBottom'} = ;
$end{'PipeRightTop'} = ;
$end{'PipeCross'} = ;
$end{'PipeVertical'} = ;
$end{'PipeHorizontal'} = ;
$end{'PipeBlank'} = ;
$end{'PipeStartUp'} = ;
$end{'PipeStartDown'} = ;
$end{'PipeStartLeft'} = ;
$end{'PipeStartRight'} = ;
$end{'PipeBlock'} = ;


sub rects {
  local ($n, $d, $i, $x1, $y1, $x1, $y2) = (@_);
  $final{$n}{$i} = 1;
  print $n, "\n";
}
