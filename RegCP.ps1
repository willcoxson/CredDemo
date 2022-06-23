# need to run in elevated prompt


$guid = "{d8ed9db5-2623-40e2-bfac-f06df0a67665}"


$cpFinalName = "HKLM:\SOFTWARE\Microsoft\Windows\CurrentVersion\Authentication\Credential Providers\$guid"
$cp = Get-Item  $cpFinalName -ea SilentlyContinue

if (-not $cp)
{
    $cp = New-Item $cpFinalName 
    if ($cp) 
    {
        $cp.SetValue("(default)", "CredTest")
    }
    else
    {
        echo "Could not create credential provider key"
    }
}

if ($cp) 
{
    regsvr32 '.\x64\release\CredDemo.dll'
}
else
{
    echo "Did not register CredDemo.dll"
}
