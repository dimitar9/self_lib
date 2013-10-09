
-- see if the file exists
function file_exists(file)
  local f = io.open(file, "rb")
  if f then f:close() end
  return f ~= nil
end

-- get all lines from a file, returns an empty 
-- list/table if the file does not exist
function lines_from(file)
  if not file_exists(file) then return {} end
  lines = {}
  for line in io.lines(file) do 
    lines[#lines + 1] = line
  end
  return lines
end

-- tests the functions above
local file = 'myfile.txt'
local lines = lines_from(file)
local i = 1

firstColword = {}    
-- print all line numbers and their contents
for k,v in pairs(lines) do
--  print('line[' .. k .. ']', v)
  words = {}
  for word in lines[i]:gmatch("%w+") do table.insert(words,word) end
  i = i+1 
  for k,v in pairs(words) do
--    print('words[' .. k .. ']', v)
    if k==1 then
      table.insert(firstColword,v)
    end
  end
end
--print first words in each line.
for i=1,#firstColword do print (firstColword[i]) end


